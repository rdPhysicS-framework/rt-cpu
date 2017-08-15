#ifndef	 __RECTANGLE_H__
#define	 __RECTANGLE_H__

#include "..\abstract\EmissiveObject.h"

class Sampler;
class AbsMaterial;

class Rectangle : public EmissiveObject
{
private:
	RT::Vec3f p;
	RT::Vec3f a;
	RT::Vec3f b;
	RT::Vec3f normal;
	Sampler *sampler;
	float area;
	float invArea;
	double aLenSquared;
	double bLenSquared;

	//AbsMaterial *material;

public:
	Rectangle(RT::Vec3f &p,
			  RT::Vec3f &a,
			  RT::Vec3f &b,
			  RT::Vec3f &normal,
			  AbsMaterial *material,
			  Sampler *sampler);
	Rectangle(RT::Vec3f &p,
			  RT::Vec3f &a,
			  RT::Vec3f &b,
			  AbsMaterial *material,
			  Sampler *sampler);
	Rectangle(const Rectangle &other);

	virtual EmissiveMaterial *GetEmissiveMaterial() const;
	virtual RT::Vec3f Sample();
	virtual float PDF(Result &result);

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);
};

#endif //__RETANGLE_H__
