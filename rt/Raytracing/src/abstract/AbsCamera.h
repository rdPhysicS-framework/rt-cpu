#ifndef	 __ABS_CAMERA_H__
#define	 __ABS_CAMERA_H__

#include "..\interface\Camera.h"

class AbsCamera : public Camera
{
protected:
	RT::Vec3f eye;
	RT::Vec3f lookAt;
	RT::Vec3f up;
	RT::Vec3f u, v, w;

	float rollAngle;
	float exposureTime;
	float zoom;

public:
	AbsCamera(RT::Vec3f &eye, 
			  RT::Vec3f &lookAt, 
			  RT::Vec3f &up,
			  float zoom,
			  float rollAngle = 0.0f);
	AbsCamera(const AbsCamera &camera);

	virtual const RT::Vec3f &GetEye() const;
	virtual const RT::Vec3f &GetLookAt() const;
	virtual const RT::Vec3f &GetEyeUp() const;

	float GetZoom() const;
	float GetRollAngle() const;
	float GetExposureTime() const;

	void SetRollAngle(float rAngle);
	void SetExposireTime(float eTime);

	void ComputeUVW();
	void DrawPixel(const AbsScene &scene, int col,
				   int row, const RT::Vec3f &color);
	virtual void Render(AbsScene &scene) = 0;
};

#endif //__ABS_CAMERA_H__
