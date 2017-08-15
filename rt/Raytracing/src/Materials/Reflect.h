#ifndef	 __REFLECT_H__
#define	 __REFLECT_H__

#include "BasicMaterial.h"

class Reflect : public BasicMaterial
{
private:
	float reflect;

public:
	Reflect(RT::Vec3f &color,
				  float diffuse,
				  float specular,
				  float intensity,
				  float reflect);
	Reflect(const Reflect &other);


	virtual Material *Clone() const;
	virtual RT::Vec3f Shade(Result &result);
	virtual RT::Vec3f AreaLightShade();
	virtual RT::Vec3f PathShade();
};

#endif //__REFLECT_H__