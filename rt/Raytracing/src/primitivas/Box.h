#ifndef	 __BOX_H__
#define	 __BOX_H__

#include "..\abstract\Primitive.h"
#include <RTmath.h>

class Box : public Primitive
{
private:
	RT::Vec3f position;
	RT::Vec3f size;

	enum Face
	{
		LEFT,
		RIGHT,
		BOTTOM,
		TOP,
		FRONT,
		BACK
	} face;

public:
	Box(RT::Vec3f &position, RT::Vec3f &size, AbsMaterial *material);
	inline RT::Vec3f GetPosition() { return position; }
	inline RT::Vec3f GetSize() { return size; }
	
	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);
	//virtual bool IntersectionShadow(Ray &ray, float &distance);
	virtual BBox GetBoundingBox() const;
};

#endif //__BOX_H__
