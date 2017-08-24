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
	void CreateScenery();
	void CreateObjects();
	void CreateIllumination();

public:
	Focus(float zoom = 1.5f, int samples = VERY_LOW);
	~Focus();

	virtual void Init();
};

#endif //__FOCUS_H__
