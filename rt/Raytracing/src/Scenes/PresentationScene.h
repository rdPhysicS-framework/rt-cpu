#ifndef	__PRESENTATION_SCENE_H__
#define __PRESENTATION_SCENE_H__

#include "..\abstract\AbsScene.h"
#include "..\Util\Util.h"

class Ray;
class Canvas;
class AbsCamera;

class PresentationScene : public AbsScene
{
private:
	Canvas *canvas;
	AbsCamera *camera;

	void CreateScenery();
	void CreateObjects();
	void CreateIllumination();

public:
	PresentationScene(float zoom = 1.5f, int samples = VERY_LOW);
	~PresentationScene();
	
	virtual Canvas *GetCanvas() const { return canvas; }
	virtual void Init();
	virtual void Render();
	virtual inline Result Hit(Ray &ray);
	virtual inline bool ShadowHit(Ray &ray, float dist);
};

#endif //__PRESENTATION_SCENE_H__
