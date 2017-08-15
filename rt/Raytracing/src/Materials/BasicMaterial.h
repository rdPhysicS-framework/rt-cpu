#ifndef	 __BASIC_MATERIAL_H__
#define	 __BASIC_MATERIAL_H__

#include "..\abstract\AbsMaterial.h"

class BasicMaterial : public AbsMaterial
{
private:
	float diffuse;
	float specular;
	float intensity;

public:
	BasicMaterial(RT::Vec3f &color,
				  float diffuse,
				  float specular,
				  float intensity);
	BasicMaterial(const BasicMaterial &other);
	

	virtual Material *Clone() const;
	virtual RT::Vec3f Shade(Result &result);
	virtual RT::Vec3f AreaLightShade();
	virtual RT::Vec3f PathShade();
};

#endif //__BASIC_MATERIAL_H__