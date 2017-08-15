#include "AbsScene.h"
#include "..\Lights\AmbientLight.h"

AbsScene::AbsScene(RT::Vec3f &background,
				   AbsLight *ambient,
				   Tracer *tracer) :
	background(background),
	ambient(ambient),
	tracer(tracer)
{}

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
}

void AbsScene::AddObjects(Primitive *object)
{
	objects.push_back(object);
}

void AbsScene::AddLights(AbsLight *light)
{
	lights.push_back(light);
}
