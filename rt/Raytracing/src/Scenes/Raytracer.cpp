#include "Raytracer.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Primitive.h"
#include "..\primitivas\Result.h"
#include "..\primitivas\Plane.h"
#include "..\primitivas\Sphere.h"
#include "..\Util\Util.h"
#include "..\raytracer\Light.h"
#include "..\raytracer\_Material.h"
#include "..\Camera\PinholeCamera.h"

Raytracer::Raytracer(float zoom) :
	AbsScene(BLACK),
	canvas(new Canvas(5120, 3840)),
	camera(new PinholeCamera(RT::Vec3f(0, 0, -8),
							 RT::Vec3f(0, 0, 0),
							 RT::Vec3f(0, 1, 0), 
							 TRACEDEPTH))
{
	Init();
}

Raytracer::~Raytracer()
{
	delete canvas;
	delete camera;
	for (Primitive *p : objects)
		delete p;
	objects.clear();

	for (Light *l : lights)
		delete l;
	lights.clear();
}

void Raytracer::Init()
{
		//chão
		objects.push_back(new Plane(RT::Vec3f(0, 1, 0), 2.0f,
			new _Material(RT::Vec3f(0.9f, 0.7f, 0.7f), 0.6f, 0.0f, 0.2f)));
	
		//parede
		objects.push_back(new Plane(RT::Vec3f(1, 0, -1).Normalize(), 12.0f,
			new _Material(RT::Vec3f(0.9f, 0.7f, 0.7f), 0.6f, 0.0f, 0.2f)));
	
		//esfera proxima da parede
		objects.push_back(new Sphere(RT::Vec3f(-5.5f, -0.5f, 6.0f), 2.0f,
			new _Material(RT::Vec3f(0.6f, 0.0f, 0.6f), 0.2f, 20.0f, 0.8f)));
	
		//esfera proxima da camera
		objects.push_back(new Sphere(RT::Vec3f(1.0f, 0.0f, 3.0f), 2.5f,
			new _Material(RT::Vec3f(0.7f, 0.8f, 0.8f), 0.9f, 20.0f, 0.3f)));
	
		//luzes
		RT::Vec3f yellow = RT::Vec3f(0.7f, 0.7f, 0.6f);
		lights.push_back(new Light(RT::Vec3f(0, 5, 5), yellow));
		lights.push_back(new Light(RT::Vec3f(2, 5, 1), yellow));
}

void Raytracer::Render()
{
	camera->Render(*this);
	canvas->Save();
}

inline RT::Vec3f Raytracer::raytrace(Ray &ray, int depth)
{
	if (depth > TRACEDEPTH)
	{
		return BLACK;
	}

	float dist = INFINITE;

	Primitive *prim = nullptr;

	for (Primitive *obj : objects)
	{
		Result result = obj->Intersect(ray, dist);

		if (result.GetHit())
		{
			dist = result.GetDistance();
			prim = obj;
		}
	}

	if (!prim)
	{
		return background;
	}

	//ponto de intersecção
	RT::Vec3f pi = ray.GetOrigin() + (ray.GetDirection() * dist);
	RT::Vec3f color = BLACK;

	for (Light *light : lights)
	{
		RT::Vec3f L = (light->GetPosition() - pi);
		float ldist = L.Size();
		L.Normalize();

		Ray shadowRay = Ray(pi, L);
		bool lit = true;

		for (Primitive *obj : objects)
		{
			if (obj->Intersect(shadowRay, ldist).GetHit())
			{
				lit = false;
				break;
			}
		}

		if (!lit)
			continue;

		RT::Vec3f N = prim->GetNormalAt(pi);

		if (prim->GetMaterial()->GetDiffuse() > 0)
		{
			float dot = N.Dot(L);

			if (dot > 0)
			{
				float diff = dot * prim->GetMaterial()->GetDiffuse();

				RT::Vec3f diffuse = (diff * light->GetColor()) * prim->GetColor();

				color += diffuse;
			}
		}

		if (prim->GetMaterial()->GetSpecular() > 0)
		{
			RT::Vec3f V = ray.GetDirection();
			RT::Vec3f R = RT::vc3::Reflect(L, N);

			float dot = V.Dot(R);

			if (dot > 0)
			{
				float specularIntensity = powf(dot, prim->GetMaterial()->GetSpecular());
				color += (specularIntensity * light->GetColor());
			}
		}
	}

	//reflecção
	float ref1 = prim->GetMaterial()->GetReflection();

	if (ref1 > 0.0)
	{
		RT::Vec3f N = prim->GetNormalAt(pi);
		RT::Vec3f R = RT::vc3::Reflect(ray.GetDirection(), N);
		RT::Vec3f rcol = raytrace(Ray(pi, R), depth + 1);
		color.Lerp(rcol, ref1);
	}

	return color;
}
