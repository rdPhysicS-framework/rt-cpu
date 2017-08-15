#ifndef	 __THIN_LENS_CAMERA_H__
#define	 __THIN_LENS_CAMERA_H__

#include "..\abstract\AbsCamera.h"

class Sampler;

class ThinLensCamera : public AbsCamera
{
private:
	float viewPlaneDistance;

	float focalDistance;
	float lensRadius;
	Sampler *sampler;

public:
	ThinLensCamera(RT::Vec3f &eye, 
				   RT::Vec3f &lookAt, 
				   RT::Vec3f &up, 
				   float viewPlaneDistance,
				   float focalDistance,
				   float lensRadius,
				   float zoom = 1.0f,
				   Sampler *sampler = nullptr);
	~ThinLensCamera();

	inline void SetFocalDistance(float vpDistance) { focalDistance = vpDistance; }
	inline void SetLensRadius(float lRadius) { lensRadius = lRadius; }
	inline void SetViewPlaneDistance(float pDistance) { viewPlaneDistance = pDistance; }
	inline void SetZoom(float _zoom) { zoom = _zoom; }
	void SetSampler(Sampler *_sampler);

	inline float GetFocalDistance() const { return focalDistance; }
	inline float GetLensRadius() const { return lensRadius; }
	inline float GetViewPlaneDistance() const { return viewPlaneDistance; }
	inline float GetZoom() const { return zoom; }
	inline Sampler *GetSampler() const { return sampler; }

	RT::Vec3f GetDirection(RT::Vec2f &pixel, RT::Vec2f &leansPoint) const;
	virtual void Render(AbsScene &scene);
};

#endif //__THIN_LENS_CAMERA_H__