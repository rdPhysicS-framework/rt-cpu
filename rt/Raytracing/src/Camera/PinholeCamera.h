#ifndef	 __PINHOLE_CAMERA_H__
#define	 __PINHOLE_CAMERA_H__

#include "..\abstract\AbsCamera.h"

class PinholeCamera : public AbsCamera
{
private:
	float viewPlaneDistance;

public:
	PinholeCamera(RT::Vec3f &eye,
				  RT::Vec3f &lookAt,
				  RT::Vec3f &up,
				  float viewPlaneDistance,
				  float zoom = 1.0f);

	float GetViewPlaneDistance() const;
	float GetZoom() const;

	void SetViewPlaneDistance(float vpDistance);
	void SetZoom(float z);

	RT::Vec3f GetDirection(RT::Vec2f &point) const;

	virtual void Render(AbsScene &scene);
};

#endif //__PINHOLE_CAMERA_H__
