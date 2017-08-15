#ifndef	 __ABS_MATERIAL_H__
#define	 __ABS_MATERIAL_H__

#include "..\interface\Material.h"

class Lambertian;
class AbsLight;

class AbsMaterial : public Material
{
protected:
	Lambertian *ambient;

public:
	AbsMaterial(const RT::Vec3f &color, float kd);
	AbsMaterial(const AbsMaterial &other);

	virtual Material *Clone() const = 0;
	virtual RT::Vec3f Shade(Result &result) = 0;
	virtual RT::Vec3f AreaLightShade(Result &result) = 0;
	virtual RT::Vec3f PathShade() = 0;
	/*virtual RT::Vec3f ProcessLight(Result &result, 
								   RT::Vec3f &wi,
								   RT::Vec3f &wo, 
								   AbsLight &light, 
								   float nDotWi) = 0;*/
};

#endif //__ABS_MATERIAL_H__