#include "AbsCamera.h"

AbsCamera::AbsCamera(RT::Vec3f &eye, 
					 RT::Vec3f &lookAt, 
					 RT::Vec3f &up,
					 float zoom,
					 float rollAngle) :
	eye(eye), lookAt(lookAt),
	up(up),   zoom(zoom),
	rollAngle(rollAngle),
	exposureTime(1.0f)
{}

AbsCamera::AbsCamera(const AbsCamera &camera) :
	eye(camera.eye), lookAt(camera.lookAt),
	up(camera.up),   zoom(camera.zoom),
	rollAngle(camera.rollAngle),
	exposureTime(camera.exposureTime)
{}

const RT::Vec3f &AbsCamera::GetEye() const
{
	return eye;
}

const RT::Vec3f &AbsCamera::GetLookAt() const
{
	return lookAt;
}

const RT::Vec3f &AbsCamera::GetEyeUp() const
{
	return up;
}

float AbsCamera::GetZoom() const
{
	return zoom;
}

float AbsCamera::GetRollAngle() const
{
	return rollAngle;
}

float AbsCamera::GetExposureTime() const
{
	return exposureTime;
}

void AbsCamera::SetRollAngle(float rAngle)
{
	rollAngle = rAngle;
}

void AbsCamera::SetExposireTime(float eTime)
{
	exposureTime = eTime;
}

void AbsCamera::ComputeUVW()
{
	w = (eye - lookAt).Normalize();

	RT::Vec3f _up = RT::vc3::Rotate(up, w, rollAngle);

	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y > lookAt.y)
	{
		u = RT::Vec3f(0, 0, 1);
		v = RT::Vec3f(1, 0, 0);
		w = RT::Vec3f(0, 1, 0);
		return;
	}

	if (eye.x == lookAt.x && eye.z == lookAt.z && eye.y < lookAt.y)
	{
		u = RT::Vec3f(1, 0, 0);
		v = RT::Vec3f(0, 0, 1);
		w = RT::Vec3f(0, -1, 0);
		return;
	}

	u = RT::vc3::Cross(_up, w).Normalize();
	v = RT::vc3::Cross(w, u).Normalize();
}

void AbsCamera::DrawPixel(const AbsScene &scene, int col,
						  int row, const RT::Vec3f &color)
{
}
