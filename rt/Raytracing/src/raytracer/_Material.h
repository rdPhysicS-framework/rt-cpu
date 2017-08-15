#ifndef	___MATERIAL_H__
#define	___MATERIAL_H__

#include <RTmath.h>

class _Material
{
private:
	RT::Vec3f color;
	float diffuse;
	float specular;
	float reflection;
	float refraction;
	float refraIndex;

public:
	_Material(RT::Vec3f color, 
			 float diffuse, 
			 float specular, 
			 float reflection,
			 float refraction = 0.0f,
		     float refraIndex = 1.5f);

	inline RT::Vec3f GetColor() { return color; }
	inline float GetDiffuse() const { return diffuse; }
	inline float GetSpecular() const { return specular; }
	inline float GetReflection() const { return reflection; }
	inline float GetRefraction() const { return refraction; }
	inline float GetRefraIndex() const { return refraIndex; }

};

#endif//___MATERIAL_H__
