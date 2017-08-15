#include "RefractionScene.h"
#include "..\raytracer\Canvas.h"
#include "..\raytracer\Ray.h"
#include "..\abstract\Primitive.h"
#include "..\Util\Util.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Light.h"
#include "..\primitivas\Plane.h"
#include "..\primitivas\Sphere.h"
#include "..\Camera\PinholeCamera.h"
#include "..\Samples\MultiJittered.h"

RefractionScene::RefractionScene(float zoom, int samples) :
	AbsScene(BLACK),
	canvas(new Canvas(1024, 768)),
	camera(new PinholeCamera(RT::Vec3f(0, 0, -5), 
						     RT::Vec3f(0, 0, 0),
						     RT::Vec3f(0, 1, 0),
						     TRACEDEPTH, 
						     zoom))
{
	canvas->SetSampler(new MultiJittered(samples));
	Init();
}

RefractionScene::~RefractionScene()
{
	delete canvas;

	for (Primitive *p : objects)
		delete p;
	objects.clear();

	for (PointLight *l : lights)
		delete l;
	lights.clear();
}

void RefractionScene::Init()
{
	//chão
	objects.push_back(new Plane(RT::Vec3f(0, 1, 0), 4.4f,
		new _Material(RT::Vec3f(0.4f, 0.3f, 0.3f), 1.0f, 0.0f, 0.0f)));

	//parede fundo
	objects.push_back(new Plane(RT::Vec3f(0.4f, 0, -1), 12.0f,
		new _Material(RT::Vec3f(0.5f, 0.3f, 0.5f), 0.6f, 0.0f, 0.0f)));

	//teto
	objects.push_back(new Plane(RT::Vec3f(0, -1, 0).Normalize(), 7.4f,
		new _Material(RT::Vec3f(0.4f, 0.7f, 0.7f), 0.5f, 0.0f, 0.0f)));
////////////////////////////////////////////////////////////////////////////////////////
	//esfera grande
	objects.push_back(new Sphere(RT::Vec3f(2.0f, 0.8f, 3.0f), 6.0f,
		new _Material(RT::Vec3f(0.7f, 0.7f, 1.0f), 0.2f, 0.8f, 0.2f, 0.8f, 1.3f)));

	//esfera proxima da parede
	objects.push_back(new Sphere(RT::Vec3f(-5.5f, -0.5f, 7.0f), 4.0f,
		new _Material(RT::Vec3f(0.7f, 0.8f, 1.0f), 0.1f, 0.8f, 0.5f)));

	//esfera proxima da camera
	objects.push_back(new Sphere(RT::Vec3f(-1.5f, -3.8f, 1.0f), 3.0f,
		new _Material(RT::Vec3f(1.0f, 0.4f, 0.4f), 0.2f, 0.8f, 0.0f)));
////////////////////////////////////////////////////////////////////////////////////////
	//esferas menores
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			objects.push_back(new Sphere(RT::Vec3f(-4.5f + x * 1.5f, -0.5f + y * 1.5f, 10.0f), 0.075f,
				new _Material(RT::Vec3f(0.3f, 1.0f, 0.4f), 0.6f, 0.6f, 0)));
		}
	}


	//luzes
	RT::Vec3f yellow = RT::Vec3f(1.0f, 1.0f, 1.0f);
	lights.push_back(new PointLight(RT::Vec3f(0, 5, 5), RT::Vec3f(0.4f, 0.4f, 0.4f)));
	lights.push_back(new PointLight(RT::Vec3f(-3, 5, 1), RT::Vec3f(0.6f, 0.6f, 0.8f)));
}

void RefractionScene::Render()
{
	camera->Render(*this);

	//salva a imagem
	canvas->Save();
}

inline RT::Vec3f RefractionScene::raytrace(Ray &ray, int depth, float index)
{
	if (depth > TRACEDEPTH)
	{
		return BLACK;
	}

	//distania maxima
	float dist = INFINITE;

	Primitive *prim = nullptr;
	int res;

	for (Primitive *obj : objects)
	{
		//guarda o resultado da intersecção
		Result result = obj->Intersect(ray, dist);

		if (int r = result.GetHit())
		{
			dist = result.GetDistance();
			prim = obj;
			res = r;
		}
	}

	if (!prim)
	{
		return background;
	}

	//ponto de intersecção
	RT::Vec3f pi = ray.GetOrigin() + (ray.GetDirection() * dist);
	RT::Vec3f color = BLACK;

	for (PointLight *light : lights)
	{
		//direção do raio até a origen da luz{
		RT::Vec3f L = (light->GetPosition() - pi);
		float ldist = L.Size();
		L.Normalize();
		// }

		//dispara um raio secundário do ponto de interseção 
		//para a luz e vê se este ponto estiver em sombras
		Ray shadowRay = Ray(pi + L * EPSILON, L);
		bool lit = true;

		//loop verificando se
		//exixte algum objeto
		//na frente do raio
		//secundário
		for (Primitive *obj : objects)
		{
			//se existir para o for 
			if (obj->Intersect(shadowRay, ldist).GetHit())
			{
				lit = false;
				break;
			}
		}

		//se existe obj
		//na frente, não
		//calcula o efeito
		//da luz
		if (!lit)
			continue;

		RT::Vec3f N = prim->GetNormalAt(pi);

		//calcula iluminação {
		if (prim->GetMaterial()->GetDiffuse() > 0)
		{
			float dot = N.Dot(L);

			if (dot > 0)
			{
				float diff = dot * prim->GetMaterial()->GetDiffuse();

				RT::Vec3f diffuse = (diff * light->GetColor()) * prim->GetColor();

				color += diffuse;
			}
		}

		if (prim->GetMaterial()->GetSpecular() > 0)
		{
			RT::Vec3f V = ray.GetDirection();
			RT::Vec3f R = RT::vc3::Reflect(L, N);

			//angulação entre o vetor da 
			//direção do raio
			//com o vetorl da reflexão
			//da luz com a normal
			float dot = V.Dot(R);

			if (dot > 0)
			{
				float specularIntensity = powf(dot, 20) * prim->GetMaterial()->GetSpecular();
				color += (specularIntensity * light->GetColor());
			}
		}
	}
	//}
	//reflection
	float refl = prim->GetMaterial()->GetReflection();

	if (refl > 0.0f)
	{
		//normal do obj em relação ao ponto de intersecção
		RT::Vec3f N = prim->GetNormalAt(pi);
		//reflexo da origem com a normal do obj
		RT::Vec3f R = RT::vc3::Reflect(ray.GetDirection(), N);
		RT::Vec3f rcol = raytrace(Ray(pi, R), depth + 1, 1.0f);
		color.Lerp(rcol, refl);
	}

	//refraction
	float refr = prim->GetMaterial()->GetRefraction();
	if (refr > 0 && depth < TRACEDEPTH)
	{
		//----------------------------teste 1-----------------------------------------
		//float rindex = prim->GetMaterial()->GetRefraIndex();
		//float n = refr/rindex;
		//RT::Vec3f N = prim->GetNormalAt(pi) * static_cast<float>(res);
		//
		///*float cosI = -N.Dot(ray.GetDirection());
		//float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);*/

		////RT::Vec3f R =(n * ray.GetDirection()) + (n * cosI - sqrtf(cosT2)) * N;
		//RT::Vec3f R = RT::vc3::Refract(ray.GetDirection(), N, n);
		//RT::Vec3f rcol = raytrace(Ray(pi + R * EPSILON, R), depth + 1, rindex);
		//color += rcol;

		//----------------------------teste2----------------------------------------
		float rindex = prim->GetMaterial()->GetRefraIndex();
		RT::Vec3f N = prim->GetNormalAt(pi) * static_cast<float>(res);

		/*float cosI = -N.Dot(ray.GetDirection());
		float cosT2 = 1.0f - n * n * (1.0f - cosI * cosI);*/

		//RT::Vec3f R =(n * ray.GetDirection()) + (n * cosI - sqrtf(cosT2)) * N;
		RT::Vec3f R = RT::vc3::Refract(ray.GetDirection(), N, refr);
		RT::Vec3f rcol = raytrace(Ray(pi + R * EPSILON, R), depth + 1, index);

		//--------------------------------original------------------------------------
		//float rindex = prim->GetMaterial()->GetRefraIndex();
		//float n = index / rindex;
		//RT::Vec3f N = prim->GetNormalAt(pi) * static_cast<float>(res);

		//RT::Vec3f R = RT::vc3::Refract(ray.GetDirection(), N, n);
		//RT::Vec3f rcol = raytrace(Ray(pi + R * EPSILON, R), depth + 1, rindex);
		////color += rcol;

		//lei da cerveja(beer's law)
		RT::Vec3f absorbace = prim->GetMaterial()->GetColor() * 0.15f * -dist;
		RT::Vec3f transparecy = RT::Vec3f(expf(absorbace.x),
										  expf(absorbace.y),
										  expf(absorbace.z));

		color += rcol * transparecy;
		
	}

	return color;
}
