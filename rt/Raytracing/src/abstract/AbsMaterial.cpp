#include "AbsMaterial.h"
#include "..\Util\Util.h"
#include "..\brdf\Lambertian.h"
#include "..\primitivas\Result.h"
#include "..\abstract\AbsLight.h"
#include "..\abstract\AbsBRDF.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\AbsScene.h"

AbsMaterial::AbsMaterial(const RT::Vec3f &color, float kd) :
	ambient(new Lambertian(color, kd))
{
}

AbsMaterial::AbsMaterial(const AbsMaterial &other) :
	ambient(dynamic_cast<Lambertian*>(
		    other.ambient->Clone()))
{}

//RT::Vec3f AbsMaterial::Shade(Result &result)
//{
//	return BLACK;
//}

//RT::Vec3f AbsMaterial::AreaLightShade(Result &result)
//{
//	return BLACK;
//}
