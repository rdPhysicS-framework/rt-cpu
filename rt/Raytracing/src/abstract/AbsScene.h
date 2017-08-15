#ifndef	 __ABS_SCENE_H__
#define	 __ABS_SCENE_H__

#include <vector>
#include <RTmath.h>
#include "..\interface\Scene.h"

class Primitive;
class PointLight;
class Canvas;
class AbsLight;
class Tracer;

class AbsScene : public Scene
{
protected:
	RT::Vec3f background;
	std::vector<Primitive*> objects;
	std::vector<AbsLight*> lights;
	AbsLight *ambient;
	Tracer *tracer;

public:
	AbsScene(RT::Vec3f &background,
			 AbsLight *ambient,
			 Tracer *tracer);
	~AbsScene();

	inline RT::Vec3f GetBackground() { return background; }
	inline const std::vector<Primitive*> &GetObjects() const { return objects; }
	inline const std::vector<AbsLight*> &GetLights() const { return lights; }
	inline AbsLight *GetAmbientLight() const { return ambient; }
	inline Tracer *GetTracer() const { return tracer; }

	virtual void AddObjects(Primitive *object);
	virtual void AddLights(AbsLight *light);

	virtual Canvas *GetCanvas() const = 0;
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual inline Result Hit(Ray &ray) = 0;
	virtual inline bool ShadowHit(Ray &ray, float dist) = 0;
};

#endif //__ABS_SCENE_H__
