#ifndef	 __PRIMITIVE_H__
#define	 __PRIMITIVE_H__

#include <RTmath.h>
#include "..\abstract\AbsMaterial.h"

class Result;
class Ray;
class BBox;

class Primitive
{
protected:
	AbsMaterial *material;

public:
	Primitive(AbsMaterial *material);
	Primitive(const Primitive &other);
	~Primitive();

	virtual void AddObject(Primitive *object);
	virtual void SetMaterial(AbsMaterial *_material) { material = _material; }
	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos) = 0;
	virtual bool Intersect(Ray &ray, float &distance, Result &result) = 0;
	//virtual bool IntersectionShadow(Ray &ray, float &distance) = 0;
	virtual BBox GetBoundingBox() const;

	virtual inline AbsMaterial *GetMaterial() const { return material; }
};

#endif //__PRIMITIVE_H__
