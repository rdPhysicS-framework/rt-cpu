#ifndef	 __RESULT_H__
#define	 __RESULT_H__

#include <RTmath.h>

class Primitive;
class Ray;
class AbsScene;
class AbsMaterial;

class Result
{
public:
	int hit;
	float distance;
	AbsMaterial *material;
	RT::Vec3f wHitPoint;
	RT::Vec3f lHitPoint;
	RT::Vec3f normal;
	Ray *ray;
	int depth;
	RT::Vec3f dir;
	AbsScene *scene;

	//temporario
	RT::Mat4f transformation;

public:
	Result(int hit, float distance);
	Result(const Result &other);
	Result(AbsScene *scene);

	inline int GetHit() const { return hit; }
	inline float GetDistance() const { return distance; }
};

#endif //__RESULT_H__
