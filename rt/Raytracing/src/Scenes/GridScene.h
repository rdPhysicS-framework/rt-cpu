#ifndef	 __GRID_SCENE_H__
#define	 __GRID_SCENE_H__

#include "..\abstract\AbsScene.h"
#include "..\Util\Util.h"

class AbsCamera;
class Grid;

class GridScene : public AbsScene
{
private:
	Grid *grid;

	void CreateScenery();
	void CreateObjects();
	void CreateIllumination();

public:
	GridScene(float zoom = 1.5f, int samples = VERY_LOW);
	~GridScene();

	virtual void Init();
};

#endif //__GRID_SCENE_H__