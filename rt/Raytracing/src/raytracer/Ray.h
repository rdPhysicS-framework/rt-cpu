#ifndef	 __RAY_H__
#define	 __RAY_H__

#include <RTmath.h>

class Ray
{
private:
	RT::Vec3f origin;
	RT::Vec3f direction;

public:
	Ray(RT::Vec3f &origin, RT::Vec3f &direction);
	Ray(const Ray &other);

	inline RT::Vec3f GetOrigin() { return origin; }
	inline RT::Vec3f GetDirection() { return direction; }
	RT::Vec3f IntersectionPoint(float dist) const;
	Ray &operator=(const Ray &other);
};

#endif //__RAY_H__
