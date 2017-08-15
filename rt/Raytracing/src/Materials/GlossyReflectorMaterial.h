#ifndef	 __GLOSSY_REFLECTOR_MATERIAL_H__
#define	 __GLOSSY_REFLECTOR_MATERIAL_H__

#include "Phong.h"

class GlossySpecular;
class Sampler;

class GlossyReflectorMaterial : public Phong
{
private:
	GlossySpecular *glossyEspecular;

public:
	GlossyReflectorMaterial(RT::Vec3f &color,
					        float ambient,
						    float diffuse,
							float specular,
							float intensity,
							float reflect,
							Sampler *sampler);
	GlossyReflectorMaterial(const GlossyReflectorMaterial &other);
	~GlossyReflectorMaterial();

	//inline void SetSamples(const int numSamples, const float exp);
	void SetKr(const float kr);
	void SetExpoent(const float exp);

	virtual Material *Clone() const;
	virtual RT::Vec3f AreaLightShade(Result &result);
};

#endif //__GLOSSY_REFLECTOR_MATERIAL_H__
