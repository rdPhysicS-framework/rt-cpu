#ifndef	 __AMBIENT_LIGHT_H__
#define	 __AMBIENT_LIGHT_H__

#include "..\abstract\AbsLight.h"

class AmbientLight : public AbsLight
{
private:
	float ls;
	RT::Vec3f color;

public:
	AmbientLight(float ls, RT::Vec3f &color);
	AmbientLight(const AmbientLight &other);

	inline float GetLs() const { return ls; }
	inline const RT::Vec3f &GetColor() const { return color; }

	void SetLs(float ls);
	void SetColor(RT::Vec3f &color);
	void SetColor(float r, float g, float b);

	virtual AbsLight *Clone();
	virtual RT::Vec3f GetDirection(Result &result);
	virtual RT::Vec3f L(Result &result);
	virtual bool InShadow(Ray &ray, Result &result);
};
#endif //__AMBIENT_LIGHT_H__