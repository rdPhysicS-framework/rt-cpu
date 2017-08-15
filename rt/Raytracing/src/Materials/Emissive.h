#ifndef	 __EMISSIVE_H__
#define	 __EMISSIVE_H__

#include "..\abstract\EmissiveMaterial.h"

class Emissive : public EmissiveMaterial
{
private:
	float ls;
	RT::Vec3f color;

public:
	Emissive(RT::Vec3f &color, float ls);
	Emissive(const Emissive &other);

	inline float GetLs() const { return ls; }
	inline const RT::Vec3f &GetColor() const { return color; }

	virtual RT::Vec3f GetLe(Result &result);
	virtual Material *Clone() const;
	virtual RT::Vec3f Shade(Result &result);
	virtual RT::Vec3f AreaLightShade(Result &result);
	virtual RT::Vec3f PathShade();
};

#endif //__EMISSIVE_H__