#ifndef	 __CAMERA_H__
#define	 __CAMERA_H__

#include <RTmath.h>

class AbsScene;
class Canvas;

class Camera
{
public:
	virtual ~Camera(){}

	virtual void Render(AbsScene &scene) = 0;
	virtual const RT::Vec3f &GetEye() const = 0;
	virtual const RT::Vec3f &GetLookAt() const = 0;
	virtual const RT::Vec3f &GetEyeUp() const = 0;
};

#endif //__CAMERA_H__