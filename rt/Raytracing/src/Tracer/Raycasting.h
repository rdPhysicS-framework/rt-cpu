#ifndef	 __RAYCASTING_H__
#define	 __RAYCASTING_H__

#include "..\interface\Tracer.h"
#include "..\Util\Util.h"

class Raycasting : public Tracer
{
private:
	int maxDepth;

public:
	Raycasting(int maxDepth = TRACEDEPTH);

	virtual RT::Vec3f Raytracer(AbsScene &scene,
								Ray &ray, 
								float &distance,
								int depth);
};

#endif //__RAYCASTING_H__