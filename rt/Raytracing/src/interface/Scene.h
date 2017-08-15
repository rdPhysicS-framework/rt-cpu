#ifndef	 __SCENE_H__
#define	 __SCENE_H__

#include <RTmath.h>

class Ray;
class Result;

class Scene
{
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual inline Result Hit(Ray &ray) = 0;
	virtual inline bool ShadowHit(Ray &ray, float dist) = 0;
};

#endif //__SCENE_H__
