#include "Instance.h"
#include "..\..\abstract\AbsMaterial.h"
#include "..\..\raytracer\Ray.h"
#include "..\..\Util\BBox.h"
#include "..\..\Util\Util.h"
#include "..\Result.h"

RT::Mat4f Instance::forwardMatrix;

Instance::Instance() :
	Primitive(nullptr),
	object(nullptr),
	invMatrix(),
	transformTexture(true)
{
	forwardMatrix.Identity();
}

Instance::Instance(Primitive *object) :
	Primitive(*object),
	object(object),
	invMatrix(),
	transformTexture(true)
{
	forwardMatrix.Identity();
}

Instance::Instance(const Instance &other) :
	Primitive(other),
	object(other.object),
	invMatrix(other.invMatrix),
	transformTexture(other.transformTexture)
{
	forwardMatrix.Identity();
}

Instance::~Instance()
{
	if(object)
	{
		delete object;
		object = nullptr;
	}
}

void Instance::SetObject(Primitive *obj)
{
	object = obj;
}

void Instance::ComputeBoundingBox()
{
	BBox objBbox = object->GetBoundingBox();

	RT::Vec3f v[8];

	v[0] = RT::Vec3f(objBbox.x0, objBbox.y0, objBbox.z0);
	v[1] = RT::Vec3f(objBbox.x1, objBbox.y0, objBbox.z0);
	v[2] = RT::Vec3f(objBbox.x1, objBbox.y1, objBbox.z0);
	v[3] = RT::Vec3f(objBbox.x0, objBbox.y1, objBbox.z0);

	v[4] = RT::Vec3f(objBbox.x0, objBbox.y0, objBbox.z1);
	v[5] = RT::Vec3f(objBbox.x1, objBbox.y0, objBbox.z1);
	v[6] = RT::Vec3f(objBbox.x1, objBbox.y1, objBbox.z1);
	v[7] = RT::Vec3f(objBbox.x0, objBbox.y1, objBbox.z1);

	v[0] = transformPoint(forwardMatrix, v[0]);
	v[1] = transformPoint(forwardMatrix, v[1]);
	v[2] = transformPoint(forwardMatrix, v[2]);
	v[3] = transformPoint(forwardMatrix, v[3]);
	v[4] = transformPoint(forwardMatrix, v[4]);
	v[5] = transformPoint(forwardMatrix, v[5]);
	v[6] = transformPoint(forwardMatrix, v[6]);
	v[7] = transformPoint(forwardMatrix, v[7]);

	forwardMatrix.Identity();

	float x0 = INFINITE;
	float y0 = INFINITE;
	float z0 = INFINITE;

	for (int i = 0; i < 8; i++)
	{
		if (v[i].x < x0)
			x0 = v[i].x;
		if (v[i].y < y0)
			y0 = v[i].y;
		if (v[i].z < z0)
			z0 = v[i].z;
	}

	/*for (int i = 0; i < 8; i++)
		if (v[i].y < y0)
			y0 = v[i].y;

	for (int i = 0; i < 8; i++)
		if (v[i].z < z0)
			z0 = v[i].z;*/
	float x1 = -INFINITE;
	float y1 = -INFINITE;
	float z1 = -INFINITE;

	for (int i = 0; i < 8; i++)
	{
		if (v[i].x > x1)
			x1 = v[i].x;
		if (v[i].y > y1)
			y1 = v[i].y;
		if (v[i].z > z1)
			z1 = v[i].z;
	}

	bbox.x0 = x0;
	bbox.y0 = y0;
	bbox.z0 = z0;
	bbox.x1 = x1;
	bbox.y1 = y1;
	bbox.z1 = z1;
}

RT::Vec3f Instance::GetNormalAt(RT::Vec3f &pos)
{
	return RT::Vec3f();
}

bool Instance::Intersect(Ray &ray, float &distance, Result &result)
{
	Ray invRay(transformPoint(invMatrix, ray.GetOrigin()),
			   transformDirection(invMatrix, ray.GetDirection()));

	if (object->Intersect(invRay, distance, result))
	{
		RT::Mat4f transform = RT::mt4::Inverse(invMatrix);
		result.wHitPoint = transformPoint(transform, result.wHitPoint);
		result.normal = transformNormal(invMatrix, result.normal);

		if (object->GetMaterial())
			material = object->GetMaterial();

		if (!transformTexture)
		{
			result.wHitPoint = ray.IntersectionPoint(distance);
			result.lHitPoint = result.wHitPoint;
		}

		return true;
	}
	
	return false;
}

BBox Instance::GetBoundingBox() const
{
	return bbox;
}

Instance &Instance::Translate(const float x, const float y, const float z)
{
	invMatrix *= RT::mt4::AffTranslation(-x, -y, -z);
	forwardMatrix = RT::mt4::AffTranslation(x, y, z) * forwardMatrix;

	return (*this);
}

Instance &Instance::Translate(const RT::Vec3f &pos)
{
	invMatrix *= RT::mt4::AffTranslation(pos*-1);
	forwardMatrix = RT::mt4::AffTranslation(pos) * forwardMatrix;

	return (*this);
}

Instance &Instance::RotateX(const float angle)
{
	float ang = RT::Math::ToRadians(angle);
	invMatrix *= RT::mt4::AffRotationX(ang).Transpose();
	forwardMatrix = RT::mt4::AffRotationX(ang) * forwardMatrix;

	return (*this);
}

Instance &Instance::RotateY(const float angle)
{
	float ang = RT::Math::ToRadians(angle);
	invMatrix *= RT::mt4::AffRotationY(ang).Transpose();
	forwardMatrix = RT::mt4::AffRotationY(ang) * forwardMatrix;

	return (*this);
}

Instance &Instance::RotateZ(const float angle)
{
	float ang = RT::Math::ToRadians(angle);
	invMatrix *= RT::mt4::AffRotationZ(ang).Transpose();
	forwardMatrix = RT::mt4::AffRotationZ(ang) * forwardMatrix;

	return (*this);
}

Instance &Instance::Scale(const float x, const float y, const float z)
{
	invMatrix *= RT::mt4::AffScaling(1.0f/x, 1.0f/y, 1.0f/z);
	forwardMatrix = RT::mt4::AffScaling(x, y, z) * forwardMatrix;

	return (*this);
}

Instance &Instance::Scale(const RT::Vec3f &scale)
{
	invMatrix *= RT::mt4::AffScaling(1.0f/scale.x, 1.0f/scale.y, 1.0f/scale.z);
	forwardMatrix = RT::mt4::AffScaling(scale) * forwardMatrix;

	return (*this);
}

Instance &Instance::Scale(const float scale)
{
	invMatrix *= RT::mt4::AffScaling(1/scale, 1/scale, 1/scale);
	forwardMatrix = RT::mt4::AffScaling(scale) * forwardMatrix;

	return (*this);
}
