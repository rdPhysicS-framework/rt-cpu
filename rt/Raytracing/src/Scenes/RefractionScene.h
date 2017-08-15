#ifndef	 __REFRACTION_SCENE_H__
#define	 __REFRACTION_SCENE_H__

#include "..\abstract\AbsScene.h"
#include "..\Util\Util.h"

class AbsCamera;
class Canvas;
class Ray;

class RefractionScene : public AbsScene
{
private:
	Canvas *canvas;
	AbsCamera *camera;

public:
	RefractionScene(float zoom = 1.5f, int samples = VERY_LOW);
	~RefractionScene();
	virtual Canvas *GetCanvas() const { return canvas; }
	virtual void Init();
	/*
	 *Percorre pixel a pixel realizando o desenho
	*/
	virtual void Render();
	/*
	 *Traça os raios a partir da posição e
	 *direção do mesmo contidos na classe
	 *raio passado por parametro. 
	 *E uma distancia maxima tambem passado 
	 *por parametro
	*/
	virtual inline RT::Vec3f raytrace(Ray &ray, int depth) { return raytrace(ray, depth, 1.0f); }
	inline RT::Vec3f raytrace(Ray &ray, int depth, float index = 1.0f);
};

#endif //__REFRACTION_SCENE_H__
