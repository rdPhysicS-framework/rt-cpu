#include "Emissive.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"

Emissive::Emissive(RT::Vec3f &color, 
				   float ls) :
	color(color),
	ls(ls)
{}

Emissive::Emissive(const Emissive &other) :
	color(other.color),
	ls(other.ls)
{}

RT::Vec3f Emissive::GetLe(Result &result)
{
	return (color * ls);
}

Material *Emissive::Clone() const
{
	return new Emissive(*this);
}

RT::Vec3f Emissive::Shade(Result &result)
{
	return  ((result.normal * -1)
		     .Dot(result.ray->
			   GetDirection()) > 0.0f)? 
			(color * ls) :
		     BLACK;
}

RT::Vec3f Emissive::AreaLightShade(Result &result)
{
	return Shade(result);
}

RT::Vec3f Emissive::PathShade()
{
	return RT::Vec3f();
}
