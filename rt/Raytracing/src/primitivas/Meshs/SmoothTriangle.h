#ifndef	 __SMOOTH_TRIANGLE_H__
#define	 __SMOOTH_TRIANGLE_H__

#include "..\..\abstract\Primitive.h"

class SmoothTriangle : public Primitive
{
private:
	RT::Vec3f v0, v1, v2;
	RT::Vec3f InterpolateNormal(const float beta, 
								const float gamma);
	RT::Vec3f normal;

public:
	RT::Vec3f n0, n1, n2;

public:
	SmoothTriangle();
	SmoothTriangle(RT::Vec3f &v0, RT::Vec3f &v1, RT::Vec3f &v2);
	SmoothTriangle(RT::Vec3f &v0, RT::Vec3f &v1, RT::Vec3f &v2,
				   RT::Vec3f &n0, RT::Vec3f &n1, RT::Vec3f &n2);
	SmoothTriangle(RT::Vec3f &v0, RT::Vec3f &v1, RT::Vec3f &v2,
				   RT::Vec3f &n0, RT::Vec3f &n1, RT::Vec3f &n2,
				   AbsMaterial *material);
	SmoothTriangle(const SmoothTriangle &other);

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);
	virtual BBox GetBoundingBox() const;
};

#endif //__SMOOTH_TRIANGLE_H__
