#ifndef	 __AREA_LIGHT_H__
#define	 __AREA_LIGHT_H__

#include "..\abstract\AbsLight.h"

class EmissiveObject;
class Material;

class AreaLight : public AbsLight
{
private:
	EmissiveObject *object;
	Material *material;
	RT::Vec3f samplePoint;
	RT::Vec3f normal;
	RT::Vec3f wi;

public:
	AreaLight(EmissiveObject *object);
	AreaLight(const AreaLight &other);

	inline EmissiveObject *GetObject() const { return object; }

	virtual AbsLight *Clone();
	virtual RT::Vec3f GetDirection(Result &result);
	virtual RT::Vec3f L(Result &result);
	virtual float G(Result &result);
	virtual float PDF(Result &result);
	virtual bool InShadow(Ray &ray, Result &result);
};

#endif //__AREA_LIGHT_H__