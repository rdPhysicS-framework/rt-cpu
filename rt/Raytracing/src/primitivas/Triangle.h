#ifndef	 __TRIANGLES_H__
#define	 __TRIANGLES_H__

#include "..\abstract\Primitive.h" 

class Triangle : public Primitive
{
private:
	RT::Vec3f v1;
	RT::Vec3f v2;
	RT::Vec3f v3;

	RT::Vec3f normal;

public:
	Triangle(RT::Vec3f &v1, 
			 RT::Vec3f &v2, 
			 RT::Vec3f &v3, 
			 AbsMaterial *material);

	Triangle(RT::Vec3f v1,
			 RT::Vec3f v2,
			 RT::Vec3f v3,
			 RT::Vec3f normal,
			 AbsMaterial *material);

	Triangle(Triangle &other);

	inline RT::Vec3f GetV1() { return v1; }
	inline RT::Vec3f GetV2() { return v2; }
	inline RT::Vec3f GetV3() { return v3; }

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);

	virtual BBox GetBoundingBox() const;
};

#endif //__TRIANGLES_H__