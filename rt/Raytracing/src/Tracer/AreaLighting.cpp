#include "AreaLighting.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"
#include "..\primitivas\Result.h"
#include "..\abstract\AbsMaterial.h"

AreaLighting::AreaLighting(int maxDepth) :
	maxDepth(maxDepth)
{}

RT::Vec3f AreaLighting::Raytracer(AbsScene &scene, 
								  Ray &ray, 
								  float &distance,
								  int depth)
{
	if (depth > maxDepth)
	{
		return BLACK;
	}

	Result result(scene.Hit(ray));//Result result(scene.Hit(ray));

	if (result.hit)
	{
		result.depth = depth;
		result.ray = &ray;
		distance = result.distance;
		return result.material->AreaLightShade(result);
	}

	distance = INFINITE;
	return scene.GetBackground();
}

