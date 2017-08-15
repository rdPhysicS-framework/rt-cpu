#ifndef	 __PHONG_H__
#define	 __PHONG_H__

#include "..\abstract\AbsMaterial.h"

class GlossySpecular;

class Phong : public AbsMaterial
{
private:
	Lambertian *diffuse;
	GlossySpecular *specular;
	float intensity;

public:
	Phong(RT::Vec3f &color,
		  float ambient,
		  float diffuse, 
		  float specular, 
		  float intensity);
	Phong(const Phong &other);
	~Phong();

	virtual Material *Clone() const;
	virtual RT::Vec3f Shade(Result &result);
	virtual RT::Vec3f AreaLightShade(Result &result);
	virtual RT::Vec3f PathShade();
	/*virtual RT::Vec3f ProcessLight(Result &result,
								   RT::Vec3f &wi,
								   RT::Vec3f &wo,
								   AbsLight &light,
								   float nDotWi);*/
};

#endif //__PHONG_H__