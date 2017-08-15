#ifndef	 __SQUARE_TRIANGLE_H__
#define	 __SQUARE_TRIANGLE_H__

#include "..\compound\Compound.h"

class SquareTriangle : public Compound
{
private:
	RT::Vec3f position;
	RT::Vec3f size;
	RT::Vec3f normal;

	void ComputeBoundingBox();
	void Create(RT::Vec3f &v0,
				RT::Vec3f &v1,
				RT::Vec3f &v2,
				RT::Vec3f &v3);

public:
	SquareTriangle(RT::Vec3f &v0, 
				   RT::Vec3f &v1,
				   RT::Vec3f &v2,
				   RT::Vec3f &v3,
				   AbsMaterial *material);

	SquareTriangle(RT::Vec3f &v0,
				   RT::Vec3f &v1,
				   RT::Vec3f &v2,
				   RT::Vec3f &v3,
				   RT::Vec3f &normal,
				   AbsMaterial *material);

	virtual bool Intersect(Ray &ray, float &distance,
		Result &result);
};

#endif //__SQUARE_TRIANGLE_H__
