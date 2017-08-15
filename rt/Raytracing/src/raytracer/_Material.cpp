#include "_Material.h"

_Material::_Material(RT::Vec3f color,
				   float diffuse, 
				   float specular, 
				   float reflection,
				   float refraction,
				   float refraIndex) :
	color(color), diffuse(diffuse),
	specular(specular), reflection(reflection),
	refraction(refraction), refraIndex(refraIndex)
{}
