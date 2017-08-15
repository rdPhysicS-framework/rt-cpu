#ifndef	 __AMBIENT_OCCLUDER_H__
#define	 __AMBIENT_OCCLUDER_H__

#include "..\abstract\AbsLight.h"

class Sampler;

class AmbientOccluder : public AbsLight
{
private:
	RT::Vec3f u;
	RT::Vec3f v;
	RT::Vec3f w;
	Sampler *sampler;
	RT::Vec3f color;
	float ls;
	float minAmount;

public:
	AmbientOccluder(RT::Vec3f &color, 
					float ls,
					float minAmount, 
					Sampler *sampler);
	AmbientOccluder(AmbientOccluder &other);
	~AmbientOccluder();

	inline Sampler *GetSampler() const { return sampler; }
	inline const RT::Vec3f &GetColor() const { return color; }

	virtual AbsLight *Clone();
	virtual RT::Vec3f GetDirection(Result &result);
	virtual RT::Vec3f L(Result &result);
	virtual bool InShadow(Ray &ray, Result &result);
};

#endif //__AMBIENT_OCCLUDER_H__