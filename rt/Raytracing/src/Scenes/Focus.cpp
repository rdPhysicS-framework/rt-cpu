#include "Focus.h"
#include "..\raytracer\Canvas.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Primitive.h"
#include "..\primitivas\Result.h"
#include "..\Lights\PointLight.h"
#include "..\primitivas\Plane.h"
#include "..\primitivas\Sphere.h"
#include "..\primitivas\Box.h"
#include "..\primitivas\Triangle.h"
#include "..\Camera\PinholeCamera.h"
#include "..\Camera\ThinLensCamera.h"
#include "..\Samples\Regular.h"
#include "..\Samples\Jittered.h"
#include "..\Samples\NRooks.h"
#include "..\Samples\Hammersley.h"
#include "..\Samples\Random.h"
#include "..\Samples\MultiJittered.h"
#include "..\Materials\Phong.h"
#include "..\Materials\ReflectMaterial.h"
#include "..\Lights\AmbientLight.h"
#include "..\Tracer\Raycasting.h"
#include "..\Materials\Reflect.h"
#include "..\Lights\AmbientOccluder.h"
#include "..\primitivas\Rectangle.h"
#include "..\Materials\Emissive.h"
#include "..\Lights\AreaLight.h"
#include "..\Tracer\AreaLighting.h"

Focus::Focus(float zoom, int samples) :
	AbsScene(BLACK,
			 new AmbientOccluder(RT::Vec3f(1.0f, 1.0f, 1.0f),
			 					 1.5f, 0.4f,
			 					 new MultiJittered(samples)),
			 new AreaLighting()),
	camera(new ThinLensCamera(RT::Vec3f(-6.5f, -1.0f, -2.5f),
							  RT::Vec3f(-5.0f, -1.0f, 0.0f),
							  RT::Vec3f(0, 1, 0),
							  12, 6.5f, 0.25f, zoom,
							  new MultiJittered(samples))),
	canvas(new Canvas(1920, 1080))
{
	canvas->SetSampler(
		new MultiJittered(samples)
		);
	Init();
}

Focus::~Focus()
{
	delete canvas;
	delete camera;
}

void Focus::CreateScenery()
{
	//chão
	AddObjects(new Plane(RT::Vec3f(0, 1, 0), 3.0f,
		new Phong(RT::Vec3f(0.4f, 0.3f, 0.3f),
			0.2f, 0.7f, 0.5f, 25.0f)));

	//parede fundo
	AddObjects(new Plane(RT::Vec3f(0, 0, -1), 22.4f,
		new Phong(RT::Vec3f(0.6f, 0.5f, 0.5f),
			0.2f, 1.0f, 0.8f, 25.0f)));

	//parede esquerda
	AddObjects(new Plane(RT::Vec3f(1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f),
			0.2f, 1.0f, 0.8f, 25.0f)));

	//parede direita
	AddObjects(new Plane(RT::Vec3f(-1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f),
			0.2f, 1.0f, 0.8f, 25.0f)));
}

void Focus::CreateObjects()
{
	//esfera de cima da caixa
	AddObjects(new Sphere(RT::Vec3f(1.5f, 0.5f, 4.0f), 2.0f,
		new ReflectMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f),
			0.2f, 0.7f, 0.8f, 20.f, 0.1f)));

	//esfera grande
	AddObjects(new Sphere(RT::Vec3f(-5.0f, -0.8f, 4.0f), 2.5f,
		new ReflectMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
			0.2f, 0.7f, 0.8f, 20.0f, 0.1f)));

	AddObjects(new Box(RT::Vec3f(0.0f, -3.0f, 2.5f), RT::Vec3f(3.0f, 1.5f, 3.0f),
		new Phong(RT::Vec3f(0.7f, 0.7f, 1.0f),
			0.2f, 0.7f, 0.2f, 20.0f)));
}

void Focus::CreateIllumination()
{
	//luzes
	Rectangle *r1 = new Rectangle(RT::Vec3f(8, 7, -2),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 20.0f),
		new MultiJittered(ULTRA));

	Rectangle *r2 = new Rectangle(RT::Vec3f(8, 6.9f, 12),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 20.0f),
		new MultiJittered(ULTRA));

	Rectangle *r3 = new Rectangle(RT::Vec3f(-8, 7, -2),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 20.0f),
		new MultiJittered(ULTRA));

	Rectangle *r4 = new Rectangle(RT::Vec3f(-8, 7, 12),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 20.0f),
		new MultiJittered(ULTRA));

	AddObjects(r1);
	AddObjects(r2);
	AddObjects(r3);
	AddObjects(r4);

	AddLights(new AreaLight(r1));
	AddLights(new AreaLight(r2));
	AddLights(new AreaLight(r3));
	AddLights(new AreaLight(r4));
}

void Focus::Init()
{
	CreateScenery();
	CreateIllumination();
	CreateObjects();
}

void Focus::Render()
{
	camera->Render(*this);
	canvas->Save();
}

Result Focus::Hit(Ray &ray)
{
	Result result(this);

	float dist = INFINITE;

	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, dist, result))
		{
			//result.hit = true;
			result.material = obj->GetMaterial();
			RT::Vec3f pi = ray.IntersectionPoint(dist);
			result.lHitPoint = pi;
			result.wHitPoint = pi;
			result.normal = obj->GetNormalAt(pi);
		}
	}
	return result;
}

bool Focus::ShadowHit(Ray &ray, float dist)
{
	Result result(this);
	float t = INFINITE;
	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, t, result) && t < dist)
			return true;
	}

	return false;
}
