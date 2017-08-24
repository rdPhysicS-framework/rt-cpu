#include "AbsScene.h"
#include "..\Lights\AmbientLight.h"
#include "..\abstract\AbsCamera.h"
#include "..\raytracer\Canvas.h"
#include "..\primitivas\Result.h"
#include "..\abstract\Primitive.h"
#include "..\Util\Util.h"

AbsScene::AbsScene(RT::Vec3f &background, 
				   AbsLight *ambient, 
				   Tracer *tracer, 
				   Canvas *canvas, 
				   AbsCamera *camera) :
	background(background),
	ambient(ambient),
	tracer(tracer),
	canvas(canvas),
	camera(camera)
{
}

AbsScene::~AbsScene()
{
	for (Primitive *p : objects)
	{
		delete p;
	}

	objects.clear();

	for (AbsLight *l : lights)
	{
		delete l;
	}

	lights.clear();

	delete ambient;
	delete tracer;
	delete canvas;
	delete camera;
}

void AbsScene::AddObjects(Primitive *object)
{
	objects.push_back(object);
}

void AbsScene::AddLights(AbsLight *light)
{
	lights.push_back(light);
}

void AbsScene::Render()
{
	camera->Render(*this);
	canvas->Save();
}

inline Result AbsScene::Hit(Ray &ray)
{
	Result result(this);
	RT::Vec3f normal;
	RT::Vec3f hitPoint;

	float dist = INFINITE;
	float t = INFINITE;

	for (Primitive *obj : objects)
	{
		if (obj->Intersect(ray, t, result))
		{
			result.hit = true;
			result.material = obj->GetMaterial();
			dist = t;
			normal = result.normal;
			hitPoint = result.wHitPoint;
			/*RT::Vec3f pi = ray.IntersectionPoint(dist);
			result.lHitPoint = pi;
			result.wHitPoint = pi;*/
			//result.normal = obj->GetNormalAt(result.wHitPoint);
		}
	}

	if (result.hit)
	{
		result.distance = dist;
		result.normal = normal;
		result.wHitPoint = hitPoint;
	}

	return result;
}

inline bool AbsScene::ShadowHit(Ray &ray, float dist)
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
