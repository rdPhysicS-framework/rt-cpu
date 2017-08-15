#ifndef	 __FOCUS_H__
#define	 __FOCUS_H__

#include "..\abstract\AbsScene.h"

#include "..\Util\Util.h"

class Ray;
class Canvas;
class AbsCamera;

class Focus : public AbsScene
{
private:
	Canvas *canvas;
	AbsCamera *camera;

	void CreateScenery();
	void CreateObjects();
	void CreateIllumination();

public:
	Focus(float zoom = 1.5f, int samples = VERY_LOW);
	~Focus();

	virtual Canvas *GetCanvas() const { return canvas; }
	virtual void Init();
	virtual void Render();
	virtual inline Result Hit(Ray &ray);
	virtual inline bool ShadowHit(Ray &ray, float dist);
};

#endif //__FOCUS_H__
