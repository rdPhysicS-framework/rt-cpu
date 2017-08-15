#include "Result.h"
#include "..\Util\Util.h"

Result::Result(int hit, float distance) :
	hit(hit), /*distance(distance),*/
	material(nullptr),
	wHitPoint(),
	lHitPoint(),
	normal(),
	ray(),
	depth(0),
	dir(),
	scene(nullptr)
{}

Result::Result(const Result &other) :
	hit(other.hit),
	//distance(other.distance),
	material(other.material),
	wHitPoint(other.wHitPoint),
	lHitPoint(other.lHitPoint),
	normal(other.normal),
	ray(other.ray),
	depth(other.depth),
	dir(other.dir),
	scene(other.scene)
{}

Result::Result(AbsScene *scene) :
	hit(0), /*distance(0.0f),*/
	material(nullptr),
	wHitPoint(),
	lHitPoint(),
	normal(),
	ray(),
	depth(0),
	dir(),
	scene(scene)
{}
