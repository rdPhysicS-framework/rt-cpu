#ifndef	 __ENVIRONMENT_LIGHT_H__
#define	 __ENVIRONMENT_LIGHT_H__

#include "..\abstract\AbsLight.h"

class EmissiveMaterial;
class Sampler;

class EnvironmentLight : public AbsLight
{
private:
	EmissiveMaterial *material;
	Sampler *sampler;
	RT::Vec3f u;
	RT::Vec3f v;
	RT::Vec3f w;
	RT::Vec3f wi;

public:
	EnvironmentLight(EmissiveMaterial *material, Sampler *sampler);
	EnvironmentLight(const EnvironmentLight &other);
	~EnvironmentLight();

	inline EmissiveMaterial *GetMaterial() const { return material; }

	virtual AbsLight *Clone();
	virtual RT::Vec3f GetDirection(Result &result);
	virtual RT::Vec3f L(Result &result);
	virtual float PDF(Result &result);
	virtual bool InShadow(Ray &ray, Result &result);
};

#endif //__ENVIRONMENT_LIGHT_H__