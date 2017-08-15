#ifndef	 __REFLECT_MATERIAL_H__
#define	 __REFLECT_MATERIAL_H__

#include "Phong.h"

class PerfectSpecular;

class ReflectMaterial : public Phong
{
private:
	PerfectSpecular *reflect;

public:
	ReflectMaterial(RT::Vec3f &color,
					float ambient,
					float diffuse,
					float specular,
					float intensity,
					float reflect);
	ReflectMaterial(const ReflectMaterial &other);
	~ReflectMaterial();

	virtual Material *Clone() const;
	virtual RT::Vec3f Shade(Result &result);
	virtual RT::Vec3f AreaLightShade(Result &result);
	virtual RT::Vec3f PathShade();
};

#endif //__REFLECT_MATERIAL_H__
