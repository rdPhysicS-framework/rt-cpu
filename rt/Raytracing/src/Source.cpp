#include <iostream>
#include "Scenes\Raytracer.h"
#include "Scenes\PresentationScene.h"
#include "Scenes\PresentationScene1.h"
#include "Scenes\Focus.h"
#include "Scenes\RefractionScene.h"
#include "Scenes\GridScene.h"
#include "interface\Scene.h"
#include "Util\Util.h"
#include <time.h>

#include <SDL.h>

int main(int argc, char **argv)
{
	GridScene(1.5f, VERY_LOW).Render();

	/*struct float3 {
		float x, y, z;
	};

	RT::Vec3f a = RT::Vec3f(20, 35, 10);
	float3 *b = (float3*)&a;
	b->y = 50;
	std::cout << b->x << ", " << b->y << ", " << b->z << std::endl;
	std::cout << a << std::endl;*/

	system("pause");
	return 0;
}