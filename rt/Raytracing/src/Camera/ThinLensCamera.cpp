#include "ThinLensCamera.h"
#include "..\abstract\AbsScene.h"
#include "..\raytracer\Canvas.h"
#include "..\abstract\Sampler.h"
#include "..\Util\Util.h"
#include "..\raytracer\Ray.h"
#include "..\Tracer\Raycasting.h"

ThinLensCamera::ThinLensCamera(RT::Vec3f &eye, 
							   RT::Vec3f &lookAt, 
							   RT::Vec3f &up, 
							   float viewPlaneDistance, 
							   float focalDistance, 
							   float lensRadius, 
							   float zoom,
							   Sampler *sampler) :
	AbsCamera(eye, lookAt, up, zoom),
	viewPlaneDistance(viewPlaneDistance),
	focalDistance(focalDistance),
	lensRadius(lensRadius), sampler(sampler)
{
	if (sampler)
		sampler->MapSamplesToUnitDisk();
}

ThinLensCamera::~ThinLensCamera()
{
	delete sampler;
	sampler = nullptr;
}

void ThinLensCamera::SetSampler(Sampler *_sampler)
{
	if (sampler)
		delete sampler;

	sampler = _sampler;
	sampler->MapSamplesToUnitDisk();
}

RT::Vec3f ThinLensCamera::GetDirection(RT::Vec2f &pixel, RT::Vec2f &leansPoint) const
{
	RT::Vec2f point = pixel * (focalDistance / viewPlaneDistance) - leansPoint;
	
	return (u * point.x +
			v * point.y +
			w * -focalDistance).Normalize();
}

void ThinLensCamera::Render(AbsScene &scene)
{
	ComputeUVW();
	Canvas *canvas = scene.GetCanvas();
	float width = canvas->GetWidthImg();
	float height = canvas->GetHeightImg();

	RT::Vec2f s = canvas->GetSizePixels();
	float t;
	int samples = canvas->GetSampler()->GetNumSamples();

	for (int y = 0; y < static_cast<int>(height) - 1; y++)
	{
		for (int x = 0; x < static_cast<int>(width) - 1; x++)
		{
			RT::Vec3f color = BLACK;
			for (int i = 0; i < samples; i++)
			{
				RT::Vec2f sp = canvas->GetSampler()->SampleUnitSquare();
				RT::Vec2f pp = RT::Vec2f( s.x * (x - 0.5f * width  + sp.x),
										 -s.y * (y - 0.5f * height + sp.y));

				RT::Vec2f dp = sampler->SampleUnitDisk();
				RT::Vec2f lp = dp * lensRadius;
				RT::Vec3f o = eye + lp.x * u + lp.y * v;

				color += scene.GetTracer()->Raytracer(scene, Ray(o, GetDirection(pp, lp)), t, 1);
				//color += scene.Hit(Ray(o, GetDirection(pp, lp)), 1);
			}

			color /= samples;
			color *= exposureTime;
			canvas->Set(x, y, color);
		}
	}
}
