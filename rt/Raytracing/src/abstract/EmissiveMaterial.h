#ifndef	 __EMISSSIVE_MATERIAL_H__
#define	 __EMISSSIVE_MATERIAL_H__

#include "AbsMaterial.h"

class EmissiveMaterial : public AbsMaterial
{
public:
	EmissiveMaterial();
	EmissiveMaterial(const EmissiveMaterial &other);

	virtual RT::Vec3f GetLe(Result &result) = 0;
	virtual Material *Clone() const = 0;
	virtual RT::Vec3f Shade(Result &result) = 0;
	virtual RT::Vec3f AreaLightShade(Result &result) = 0;
	virtual RT::Vec3f PathShade() = 0;
};

#endif //__EMISSSIVE_MATERIAL_H__
