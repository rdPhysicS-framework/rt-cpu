#ifndef	 __AREA_LIGHTING_H__
#define	 __AREA_LIGHTING_H__

#include "..\interface\Tracer.h"
#include "..\Util\Util.h"

class AreaLighting : public Tracer
{
private:
	int maxDepth;

public:
	AreaLighting(int maxDepth = TRACEDEPTH);

	virtual RT::Vec3f Raytracer(AbsScene &scene,
							    Ray &ray, 
								float &distance,
								int depth);
};

#endif //__AREA_LIGHTING_H__