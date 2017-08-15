#include "Raycasting.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Ray.h"
#include "..\primitivas\Result.h"
#include "..\abstract\AbsMaterial.h"
#include "..\Util\Util.h"

Raycasting::Raycasting(int maxDepth) :
	maxDepth(maxDepth)
{}

RT::Vec3f Raycasting::Raytracer(AbsScene &scene,
								Ray &ray, 
								float &distance,
								int depth)
{
	if (depth > maxDepth)
	{
		return BLACK;
	}

	Result result(scene.Hit(ray));//Result result(scene.Hit(ray));

	if (result.hit || result.hit == EOF)
	{
		result.depth = depth;
		result.ray = &ray;
		distance = result.distance;
		return result.material->Shade(result);
	}

	distance = INFINITE;
	return scene.GetBackground();
}
