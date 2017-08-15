#ifndef	 __POINT_LIGHT_H__
#define	 __POINT_LIGHT_H__

#include "..\abstract\AbsLight.h"
#include <RTmath.h>

class PointLight : public AbsLight
{
private:
	RT::Vec3f position;
	RT::Vec3f color;
	float ls;

public:
	PointLight(RT::Vec3f &pos, RT::Vec3f &color, float ls = 1.0f);
	PointLight(const PointLight &other);

	inline RT::Vec3f GetPosition() { return position; }
	inline RT::Vec3f GetColor() { return color; }
	inline float GetLs() { return ls; }

	virtual AbsLight *Clone();
	virtual RT::Vec3f GetDirection(Result &result);
	virtual RT::Vec3f L(Result &result);
	virtual bool InShadow(Ray &ray, Result &result);
};

#endif //__POINT_LIGHT_H__
