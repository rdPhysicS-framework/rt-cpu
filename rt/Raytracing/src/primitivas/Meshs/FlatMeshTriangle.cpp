#include "FlatMeshTriangle.h"
#include "Mesh.h"
#include "..\Result.h"
#include "..\..\raytracer\Ray.h"
#include "..\..\Util\Util.h"

FlatMeshTriangle::FlatMeshTriangle() :
	MeshTriangle()
{}

FlatMeshTriangle::FlatMeshTriangle(Mesh *mesh, const int index0, 
								   const int index1, const int index2) :
	MeshTriangle(mesh, index0, index1, index2)
{}

FlatMeshTriangle::FlatMeshTriangle(const FlatMeshTriangle & other) :
	MeshTriangle(other)
{}

bool FlatMeshTriangle::Intersect(Ray &ray, float &distance, Result &result)
{
	RT::Vec3f v0(mesh->vertices[index0]);
	RT::Vec3f v1(mesh->vertices[index1]);
	RT::Vec3f v2(mesh->vertices[index2]);

	//std::cout << v0 << std::endl;
	//std::cout << v1 << std::endl;
	//std::cout << v2 << std::endl;

	double a = v0.x - v1.x;
	double b = v0.x - v2.x;
	double c = ray.GetDirection().x;
	double d = v0.x - ray.GetOrigin().x;

	double e = v0.y - v1.y;
	double f = v0.y - v2.y;
	double g = ray.GetDirection().y;
	double h = v0.y - ray.GetOrigin().y;

	double i = v0.z - v1.z;
	double j = v0.z - v2.z;
	double k = ray.GetDirection().z;
	double l = v0.z - ray.GetOrigin().z;

	double m = f * k - g * j;
	double n = h * k - g * l;
	double p = f * l - h * j;
	double q = g * i - e * k;
	double s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	if (beta < 0.0)
		return false;

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	if (gamma < 0.0)
		return false;

	if (beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	if (t < EPSILON)
		return false;

	distance = t;

	result.normal = normal;
	result.wHitPoint = ray.IntersectionPoint(distance);
	result.lHitPoint = result.wHitPoint;

	return true;
}
