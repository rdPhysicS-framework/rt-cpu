#include "PresentationScene1.h"
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
#include "..\Lights\EnvironmentLight.h"
#include "..\Tracer\AreaLighting.h"

PresentationScene1::PresentationScene1(float zoom, int samples) :
	AbsScene(BLACK, 
		/*new AmbientLight(0.2f, 
			RT::Vec3f(1.0f, 1.0f, 1.0f)),*/ 
		new AmbientOccluder(RT::Vec3f(1.0f, 1.0f, 1.0f),
						    1.5f, 0.4f,
							new MultiJittered(samples)),
		new Raycasting()),
	camera(new PinholeCamera(RT::Vec3f(-6.5f, -1.0f, -4.5f),
							 RT::Vec3f(-5.0f, -1.0f, 0.0f),
							 RT::Vec3f(0, 1, 0),
							 6,
							 zoom)),
	/*camera(new ThinLensCamera(RT::Vec3f(-6.5f, -1.0f, -2.5f),
							  RT::Vec3f(-5.0f, -1.0f, 0.0f),
							  RT::Vec3f(0, 1, 0),
							  12, 6.5f, 0.25f, zoom,
							  new MultiJittered(samples))),*/
	canvas(new Canvas(1920, 1080))
{
	canvas->SetSampler(
		new MultiJittered(samples)
		);
	Init();
}

PresentationScene1::~PresentationScene1()
{
	delete canvas;
	delete camera;
}

void PresentationScene1::Init()
{
	//chão
	objects.push_back(new Plane(RT::Vec3f(0, 1, 0), 3.0f,
		new Phong(RT::Vec3f(0.4f, 0.3f, 0.3f), 0.2f, 0.7f, 0.5f, 20.0f)));

	//parede fundo
	objects.push_back(new Plane(RT::Vec3f(0, 0, -1), 22.4f,
		new Phong(RT::Vec3f(0.6f, 0.5f, 0.5f), 0.2f, 1.0f, 0.8f, 20.0f)));

	//parede esquerda
	objects.push_back(new Plane(RT::Vec3f(1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f), 0.2f, 1.0f, 0.8f, 20.0f)));
	
	//parede direita
	objects.push_back(new Plane(RT::Vec3f(-1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f), 0.2f, 1.0f, 0.8f, 20.0f)));

	////teto
	//objects.push_back(new Plane(RT::Vec3f(0, -1, 0), 5.2f,
	//	new Phong(RT::Vec3f(0.7f, 0.7f, 0.7f), 0.2f, 1.0f, 0.8f, 20.0f)));
    
	//esfera de cima da caixa
	objects.push_back(new Sphere(RT::Vec3f(1.5f, 0.5f, 4.0f), 4.0f,
		new ReflectMaterial(RT::Vec3f(0.6f, 0.6f, 0.6f), 0.2f, 0.7f, 0.8f, 20.f, 0.1f)));

	//esfera grande
	objects.push_back(new Sphere(RT::Vec3f(-5.0f, -0.8f, 4.0f), 5.0f,
		new ReflectMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f), 0.2f, 0.7f, 0.8f, 20.0f, 0.1f)));

	objects.push_back(new Box(RT::Vec3f(0.0f, -3.0f, 2.5f), RT::Vec3f(3.0f, 1.5f, 3.0f),
		new Phong(RT::Vec3f(0.7f, 0.7f, 1.0f), 0.2f, 0.7f, 0.2f, 20.0f)));

	//luzes
	//RT::Vec3f yellow = RT::Vec3f(1.0f, 1.0f, 1.0f);
	//RT::Vec3f(0.0f, -3.0f, 2.5f), RT::Vec3f(3.0f, 1.5f, 3.0f)
	/*Rectangle *r1 = new Rectangle(RT::Vec3f(8, 7, -2),
								 RT::Vec3f(2, 0, 0),
								 RT::Vec3f(0, 0, 2),
								 RT::Vec3f(0, -1, 0),
								 new Emissive(RT::Vec3f(1.0f, 1.0f, 0.5f), 10.0f),
								 new MultiJittered(ULTRA));

	Rectangle *r2 = new Rectangle(RT::Vec3f(8,  6.9f, 12),
								  RT::Vec3f(2,  0,  0),
								  RT::Vec3f(0,  0,  2),
								  RT::Vec3f(0, -1,  0),
								  new Emissive(RT::Vec3f(1.0f, 1.0f, 0.5f), 10.0f),
								  new MultiJittered(ULTRA));

	Rectangle *r3 = new Rectangle(RT::Vec3f(-8, 7, -2),
								  RT::Vec3f(2, 0, 0),
								  RT::Vec3f(0, 0, 2),
								  RT::Vec3f(0, -1, 0),
								  new Emissive(RT::Vec3f(1.0f, 1.0f, 0.5f), 10.0f),
								  new MultiJittered(ULTRA));

	Rectangle *r4 = new Rectangle(RT::Vec3f(-8, 7, 12),
								  RT::Vec3f(2, 0, 0),
								  RT::Vec3f(0, 0, 2),
								  RT::Vec3f(0, -1, 0),
								  new Emissive(RT::Vec3f(1.0f, 1.0f, 0.5f), 10.0f),
								  new MultiJittered(ULTRA));
*/
	//objects.push_back(r1);
	//objects.push_back(r2);
	//objects.push_back(r3);
	//objects.push_back(r4);
	/*Rectangle *r = new Rectangle(RT::Vec3f(2, 4, -8),
								 RT::Vec3f(4, 0, 0),
								 RT::Vec3f(0, 0, 4),
								 RT::Vec3f(0, -1, 0),
								 new Emissive(WHITE, 40.0f),
								 canvas->GetSampler()->Clone());*/

	//lights.push_back(new EnvironmentLight(r1->GetEmissiveMaterial(), new MultiJittered(ULTRA)));
	//lights.push_back(new EnvironmentLight(r2->GetEmissiveMaterial(), new MultiJittered(ULTRA)));
	//lights.push_back(new EnvironmentLight(r3->GetEmissiveMaterial(), new MultiJittered(ULTRA)));
	//lights.push_back(new EnvironmentLight(r4->GetEmissiveMaterial(), new MultiJittered(ULTRA)));
	//lights.push_back(new AreaLight(r));
	lights.push_back(new PointLight(RT::Vec3f(4, 4, -4), RT::Vec3f(0.6f, 0.6f, 0.7f)));
	lights.push_back(new PointLight(RT::Vec3f(2, 5, -2), RT::Vec3f(0.5f, 0.8f, 0.8f)));
}

void PresentationScene1::Render()
{
	camera->Render(*this);
	canvas->Save();
}

Result PresentationScene1::Hit(Ray &ray)
{
	Result result(this);

	float dist = INFINITE;

	Primitive *prim = nullptr;

	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, dist, result))
		{
			//result.hit = true;
			result.material = obj->GetMaterial();
			prim = obj;
		}
	}
		//ponto de intersecção
		RT::Vec3f pi = ray.IntersectionPoint(dist);

		result.lHitPoint = pi;
		result.wHitPoint = pi;
	if (prim)
	{
		result.normal = prim->GetNormalAt(pi);
	}
	return result;
}

bool PresentationScene1::ShadowHit(Ray &ray, float dist)
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