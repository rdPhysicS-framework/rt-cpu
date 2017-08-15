#ifndef	 __Plane_H__
#define	 __Plane_H__

#include "..\abstract\Primitive.h"

class Plane : public Primitive
{
private:
	RT::Vec3f normal;
	float distance;

public:
	Plane(RT::Vec3f &normal, float distance, AbsMaterial *material);
	
	inline RT::Vec3f GetNormal() { return normal; }
	inline float GetDistance() const { return distance; }

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);
	//virtual bool IntersectionShadow(Ray &ray, float &distance);
};

#endif //__Plane_H__
