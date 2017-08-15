#ifndef	 __RAYTRACER_H__
#define	 __RAYTRACER_H__

#include "..\raytracer\Canvas.h"
#include "..\abstract\AbsScene.h"

class Ray;
class AbsCamera;

class Raytracer : public AbsScene
{
private:
	Canvas *canvas;
	AbsCamera *camera;

public:
	Raytracer(float zoom = 1.5f);
	~Raytracer();

	virtual Canvas *GetCanvas() const { return canvas; }
	virtual void Init();
	virtual void Render();
	virtual inline RT::Vec3f raytrace(Ray &ray, int depth);
};

#endif //__RAYTRACER_H__
