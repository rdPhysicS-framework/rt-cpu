#ifndef	 __TRANSPARENT_H__
#define	 __TRANSPARENT_H__

#include "Phong.h"

class PerfectSpecular;
class PerfectTransmitter;

class Transparent : public Phong
{
private:
	PerfectSpecular *reflective;
	PerfectTransmitter *specular;

public:
	Transparent(RT::Vec3f &color,
				float ambient,
				float diffuse,
				float specular,
				float intensity,
				float ks,
				float kt,
				float ior);
	Transparent(const Transparent &other);

	virtual Material *Clone() const;
	virtual RT::Vec3f Shade(Result &result);
	virtual RT::Vec3f AreaLightShade(Result &result);
	virtual RT::Vec3f PathShade();

};

#endif //__TRANSPARENT_H__