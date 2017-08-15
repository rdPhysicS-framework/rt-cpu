#include "Ray.h"
#include "..\Util\Util.h"

Ray::Ray(RT::Vec3f &origin, RT::Vec3f &direction) :
	origin(origin + (direction * EPSILON)),
	direction(direction)
{
	//this->origin = origin + (direction * EPSILON);
}

Ray::Ray(const Ray &other) :
	origin(other.origin),
	direction(other.direction)
{}

RT::Vec3f Ray::IntersectionPoint(float dist) const
{
	return origin + (direction * dist);
}

Ray &Ray::operator=(const Ray &other)
{
	if (this != &other)
	{
		origin = other.origin;
		direction = other.direction;
	}

	return (*this);
}
