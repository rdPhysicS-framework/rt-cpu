#ifndef	 __EMISSIVE_OBJECT_H__
#define	 __EMISSIVE_OBJECT_H__

#include "Primitive.h"
class EmissiveMaterial;
class AbsMaterial;

class EmissiveObject : public Primitive
{
public:
	EmissiveObject(AbsMaterial *material);
	EmissiveObject(const EmissiveObject &other);
	virtual ~EmissiveObject() {}

	virtual EmissiveMaterial *GetEmissiveMaterial() const = 0;

	virtual RT::Vec3f Sample() = 0;
	virtual float PDF(Result &result) = 0;

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos) = 0;
	virtual bool Intersect(Ray &ray, float &distance, Result &result) = 0;
};

#endif //__EMISSIVE_OBJECT_H__