#include "Reflect.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"
#include "..\primitivas\Result.h"
#include "..\abstract\AbsScene.h"
#include "..\Lights\AmbientLight.h"
#include "..\Tracer\Raycasting.h"

Reflect::Reflect(RT::Vec3f &color, 
				 float diffuse, 
				 float specular, 
				 float intensity, 
				 float reflect) :
	BasicMaterial(color, 
				  diffuse, 
				  specular, 
				  intensity), 
	reflect(reflect)
{}

Reflect::Reflect(const Reflect &other) :
	BasicMaterial(other),
	reflect(other.reflect)
{}

Material *Reflect::Clone() const
{
	return new Reflect(*this);
}

RT::Vec3f Reflect::Shade(Result &result)
{
	RT::Vec3f L = BasicMaterial::Shade(result);

	if (reflect > 0)
	{
		RT::Vec3f wo = result.ray->GetDirection();
		RT::Vec3f r = RT::vc3::Reflect(wo, result.normal);
		RT::Vec3f rColor = result.scene
								  ->GetTracer()
								  ->Raytracer(
									  *result.scene,
									  Ray(result.wHitPoint, r), 
									  result.depth + 1);
		L.Lerp(rColor, reflect);
	}

	return L;
}

RT::Vec3f Reflect::AreaLightShade()
{
	return RT::Vec3f();
}

RT::Vec3f Reflect::PathShade()
{
	return RT::Vec3f();
}
