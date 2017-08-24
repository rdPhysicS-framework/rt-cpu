#include "GridScene.h"
#include "..\raytracer\Canvas.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Primitive.h"
#include "..\primitivas\Result.h"
#include "..\Lights\PointLight.h"
#include "..\primitivas\Plane.h"
#include "..\primitivas\Sphere.h"
#include "..\primitivas\Box.h"
#include "..\primitivas\Triangle.h"
#include "..\Camera\PinholeCamera.h"
#include "..\Camera\ThinLensCamera.h"
#include "..\Samples\Regular.h"
#include "..\Samples\Jittered.h"
#include "..\Samples\NRooks.h"
#include "..\Samples\Hammersley.h"
#include "..\Samples\Random.h"
#include "..\Samples\MultiJittered.h"
#include "..\Materials\Phong.h"
#include "..\Materials\ReflectMaterial.h"
#include "..\Lights\AmbientLight.h"
#include "..\Tracer\Raycasting.h"
#include "..\Materials\Reflect.h"
#include "..\Lights\AmbientOccluder.h"
#include "..\primitivas\Rectangle.h"
#include "..\Materials\Emissive.h"
#include "..\Lights\AreaLight.h"
#include "..\Tracer\AreaLighting.h"
#include "..\primitivas\grid\Grid.h"
#include "..\primitivas\Meshs\MeshSphere.h"
#include "..\primitivas\instance\Instance.h"
#include "..\Materials\Transparent.h"

GridScene::GridScene(float zoom, int samples) :
	AbsScene(BLACK,
		/*new AmbientLight(0.2f,
		RT::Vec3f(1.0f, 1.0f, 1.0f)),*/
		new AmbientOccluder(RT::Vec3f(1.0f, 1.0f, 1.0f),
							1.5f, 0.4f,
							new MultiJittered(samples)),
		new AreaLighting(3),
		new Canvas(1920, 1080, new MultiJittered(samples)), 
		new PinholeCamera(RT::Vec3f(6.5f, -1.0f, -2.5f),
						  RT::Vec3f(4.0f, -1.0f, 0.0f),
						  RT::Vec3f(0, 1, 0),
						  8,
						  zoom)),
	grid(new Grid())
{
	Init();
}

GridScene::~GridScene()
{
}

void GridScene::CreateScenery()
{
	//chão
	AddObjects(new Plane(RT::Vec3f(0, 1, 0), 3.0f,
		new Phong(RT::Vec3f(0.4f, 0.3f, 0.3f),
			0.2f, 0.7f, 0.5f, 25.0f)));

	//parede fundo
	AddObjects(new Plane(RT::Vec3f(0, 0, -1), 22.4f,
		new Phong(RT::Vec3f(0.6f, 0.5f, 0.5f),
			0.2f, 1.0f, 0.8f, 25.0f)));

	//parede esquerda
	AddObjects(new Plane(RT::Vec3f(1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f),
			0.2f, 1.0f, 0.8f, 25.0f)));

	//parede direita
	AddObjects(new Plane(RT::Vec3f(-1, 0, 0), 12.0f,
		new Phong(RT::Vec3f(0.5f, 0.5f, 0.6f),
			0.2f, 1.0f, 0.8f, 25.0f)));
}

void GridScene::CreateObjects()
{
	//esfera de cima da caixa
	Transparent *t = new Transparent(RT::Vec3f(0.65f, 0.45f, 0), 0.2f, 0.7f, 0.5f, 2000.0f, 0.1f, 0.9f, 1.5f);
	//AddObjects(new Sphere(RT::Vec3f(1.5f, -1.0f, 4.0f), 2.0f, t
	//	/*new Phong(RT::Vec3f(0.6f, 0.6f, 0.6f),
	//		0.2f, 0.7f, 0.8f, 20.f)*/));

	//esfera grande
	AddObjects(new Sphere(RT::Vec3f(-5.0f, -0.8f, 4.0f), 2.23f,
		new ReflectMaterial(RT::Vec3f(0.7f, 0.7f, 1.0f),
			0.2f, 0.7f, 0.8f, 20.0f, 0.4f)));

	//caixa
	AddObjects(new Box(RT::Vec3f(-0.5f, -3.0f, 2.0f), RT::Vec3f(4.5f, 0.25f, 4.5f),
		new Phong(RT::Vec3f(0.5f, 0.4f, 0.4f),
			0.2f, 0.7f, 0.2f, 20.0f)));

	/*grid->AddObject(new MeshSphere(RT::Vec3f(1.5f, 0.5f, 4.0f),
		new Phong(RT::Vec3f(0.6f, 0.6f, 0.6f), 0.2f, 0.7f, 0.8f, 20.0f),
		2.0f, 30, 30));*/

	grid->ReadSmoothTriangles("plyFiles/Horse97K.ply");
	grid->SetMaterial(t);//new ReflectMaterial(RT::Vec3f(1.0f, 1.0f, 1.0f),
								//0.2f, 0.7f, 0.8f, 20.0f, 0.2f));
	grid->SetupCells();

	Grid *instanceGrid = new Grid();

	Instance *i = new Instance();
	i->SetObject(grid);
	i->Scale(6);
	i->RotateY(135.0f);
	i->Translate(1.5f, -0.95f, 3.5f);
	//i->Scale(2.f);
	i->ComputeBoundingBox();
	instanceGrid->AddObject(i);
	instanceGrid->SetupCells();

	AddObjects(instanceGrid);

	/*teste*/
	Sphere s = Sphere(RT::Vec3f(0, 0, 0), 3, nullptr);
	Ray ray = Ray(RT::Vec3f(0, 0, -3), RT::Vec3f(0, 0, 1));
	Result r = Result(nullptr);
	float tmin;
	if (s.Intersect(ray, tmin, r))
	{
		r.hit = 1;
	}
	std::cout << r.normal << std::endl;
	std::cout << r.wHitPoint << std::endl;

}

void GridScene::CreateIllumination()
{
	//luzes
	Rectangle *r1 = new Rectangle(RT::Vec3f(8, 7, -2),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 30.0f),
		new MultiJittered(ULTRA));

	Rectangle *r2 = new Rectangle(RT::Vec3f(8, 7, 12),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 30.0f),
		new MultiJittered(ULTRA));

	Rectangle *r3 = new Rectangle(RT::Vec3f(-8, 7, -2),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 30.0f),
		new MultiJittered(ULTRA));

	Rectangle *r4 = new Rectangle(RT::Vec3f(-8, 7, 12),
		RT::Vec3f(2, 0, 0),
		RT::Vec3f(0, 0, 2),
		RT::Vec3f(0, -1, 0),
		new Emissive(WHITE, 30.0f),
		new MultiJittered(ULTRA));

	AddObjects(r1);
	AddObjects(r2);
	AddObjects(r3);
	AddObjects(r4);

	AddLights(new AreaLight(r1));
	AddLights(new AreaLight(r2));
	AddLights(new AreaLight(r3));
	AddLights(new AreaLight(r4));

	/*lights.push_back(new PointLight(RT::Vec3f(4, 4, -4), RT::Vec3f(0.6f, 0.6f, 0.7f)));
	lights.push_back(new PointLight(RT::Vec3f(2, 5, -2), RT::Vec3f(0.5f, 0.8f, 0.8f)));*/
}

void GridScene::Init()
{
	CreateScenery();
	CreateIllumination();
	CreateObjects();

	/*Instance *i = new Instance();
	i->SetObject(grid);
	i->Scale(2.0f);
	grid->SetupCells();
	AddObjects(i);*/
}
