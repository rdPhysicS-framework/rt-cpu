#ifndef	 __SPHERE_H__
#define	 __SPHERE_H__

#include "..\abstract\Primitive.h"

class Sphere : public Primitive
{
private:
	RT::Vec3f center;
	RT::Vec3f normal;
	float radius;
	float sqrRadius;
	float invRadius;

public:
	Sphere(RT::Vec3f &pos, float r, AbsMaterial *material);

	inline RT::Vec3f GetCenter() { return center; }
	inline float GetRadius() const { return radius; }

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);
	//virtual bool IntersectionShadow(Ray &ray, float &distance);
	virtual BBox GetBoundingBox() const;
};
#endif //__SPHERE_H__
