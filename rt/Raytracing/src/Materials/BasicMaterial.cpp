#include "BasicMaterial.h"
#include "..\primitivas\Result.h"
#include "..\Tracer\Raycasting.h"
#include "..\abstract\AbsScene.h"
#include "..\abstract\AbsLight.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"

BasicMaterial::BasicMaterial(RT::Vec3f &color, 
							 float diffuse, 
							 float specular, 
							 float intensity) :
	AbsMaterial(color),
	diffuse(diffuse),
	specular(specular),
	intensity(intensity)
{}

BasicMaterial::BasicMaterial(const BasicMaterial &other) :
	AbsMaterial(other),
	diffuse(other.diffuse),
	specular(other.specular),
	intensity(other.intensity)
{}

Material *BasicMaterial::Clone() const
{
	return new BasicMaterial(*this);
}

RT::Vec3f BasicMaterial::Shade(Result &result)
{
	RT::Vec3f wo = result.ray->GetDirection();
	RT::Vec3f L = BLACK;

	const std::vector<AbsLight*> &lights = result.scene->GetLights();

	for (AbsLight *l : lights)
	{
		RT::Vec3f wi = l->GetDirection(result);

		if (!l->InShadow(Ray(result.wHitPoint, wi),
			result))
		{
			if (diffuse > 0)
			{
				float dot = result.normal.Dot(wi);
				if (dot > 0.0f)
				{
					float diff = dot * diffuse;
					L += l->L(result) * diff * color;
				}
			}

			if (specular > 0)
			{
				RT::Vec3f r = RT::vc3::Reflect(wi, result.normal);

				float dot = wo.Dot(r);
				if (dot > 0)
				{
					float sIntensity = powf(dot, intensity) * specular;
					L += l->L(result) * sIntensity;
				}
			}
		}
	}

	return L;
}

RT::Vec3f BasicMaterial::AreaLightShade()
{
	return RT::Vec3f();
}

RT::Vec3f BasicMaterial::PathShade()
{
	return RT::Vec3f();
}
