#ifndef	 __TRACER_H__
#define	 __TRACER_H__

#include <RTmath.h>

class AbsScene;
class Ray;

class Tracer
{
public:
	virtual RT::Vec3f Raytracer(AbsScene &scene, 
								Ray &ray, 
								float &distance,
								int depth) = 0;
};

#endif //__TRACER_H__