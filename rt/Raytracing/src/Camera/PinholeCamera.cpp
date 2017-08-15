#include "PinholeCamera.h"
#include "..\raytracer\Canvas.h"
#include "..\Util\Util.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Sampler.h"
#include "..\Tracer\Raycasting.h"

#include <RTmath.h>

PinholeCamera::PinholeCamera(RT::Vec3f &eye, 
							 RT::Vec3f &lookAt, 
							 RT::Vec3f &up, 
							 float viewPlaneDistance,
							 float zoom) :
	AbsCamera(eye, lookAt, up, zoom),
	viewPlaneDistance(viewPlaneDistance)
{
	//rollAngle = RT::Math::ToRadians(180.0);
}

float PinholeCamera::GetViewPlaneDistance() const
{
	return viewPlaneDistance;
}

float PinholeCamera::GetZoom() const
{
	return zoom;
}

void PinholeCamera::SetViewPlaneDistance(float vpDistance)
{
	viewPlaneDistance = vpDistance;
}

void PinholeCamera::SetZoom(float z)
{
	zoom = z;
}

RT::Vec3f PinholeCamera::GetDirection(RT::Vec2f &point) const
{
	return (u * point.x +
			v * point.y +
		    w * -viewPlaneDistance).Normalize();
}

void PinholeCamera::Render(AbsScene &scene)
{
	ComputeUVW();
	Canvas *canvas = scene.GetCanvas();
	float width = canvas->GetWidthImg();
	float height = canvas->GetHeightImg();

	RT::Vec2f s = canvas->GetSizePixels() / zoom;

	int samples = canvas->GetSampler()->GetNumSamples();
	float t;

	for (int y = 0; y < static_cast<int>(height); y++)
	{
		for (int x = 0; x < static_cast<int>(width); x++)
		{
			RT::Vec3f color = BLACK;
			for (int i = 0; i < samples; i++)
			{
				RT::Vec2f sp = canvas->GetSampler()->SampleUnitSquare();
				RT::Vec2f pp = RT::Vec2f( s.x * (x - 0.5f * width + sp.x),
										 -s.y * (y - 0.5f * height + sp.y));
				//scene.Hit(Ray(eye, GetDirection(pp)), 1);
				color += scene.GetTracer()->Raytracer(scene, Ray(eye, GetDirection(pp)), t, 1);
			}

			color /= samples;
			color *= exposureTime;
			canvas->Set(x, y, color);
		}
	}
}
