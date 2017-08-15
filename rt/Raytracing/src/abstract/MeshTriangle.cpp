#include "MeshTriangle.h"
#include "..\primitivas\Meshs\Mesh.h"
#include "..\Util\Util.h"
#include "..\Util\BBox.h"


MeshTriangle::MeshTriangle() :
	Primitive(nullptr),
	mesh(nullptr),
	index0(0),
	index1(0),
	index2(0),
	normal()
{}

MeshTriangle::MeshTriangle(Mesh *mesh, const int index0, 
						   const int index1, const int index2) :
	Primitive(nullptr),
	mesh(mesh),
	index0(index0),
	index1(index1),
	index2(index2),
	normal()
{}

MeshTriangle::MeshTriangle(const MeshTriangle &other) :
	Primitive(nullptr),
	mesh(other.mesh),
	index0(other.index0),
	index1(other.index1),
	index2(other.index2),
	normal(other.normal)
{}

MeshTriangle::~MeshTriangle()
{
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
}

RT::Vec3f MeshTriangle::GetNormalAt(RT::Vec3f & pos)
{
	return normal;
}

void MeshTriangle::ComputeNormal(const bool reverseNormal)
{
	normal = (mesh->vertices[index1] - 
			  mesh->vertices[index0]  ).Cross(
					  mesh->vertices[index2] -
					  mesh->vertices[index0]   ).Normalize();

	if (reverseNormal)
		normal = normal * -1;
}

BBox MeshTriangle::GetBoundingBox() const
{
	double delta = EPSILON;

	RT::Vec3f v0(mesh->vertices[index0]);
	RT::Vec3f v1(mesh->vertices[index1]);
	RT::Vec3f v2(mesh->vertices[index2]);

	return BBox(min(min(v0.x, v1.x), v2.x) - delta, 
				min(min(v0.y, v1.y), v2.y) - delta, 
				min(min(v0.z, v1.z), v2.z) - delta,
				max(max(v0.x, v1.x), v2.x) + delta, 
				max(max(v0.y, v1.y), v2.y) + delta, 
			    max(max(v0.z, v1.z), v2.z) + delta);
}

float MeshTriangle::InterpolateU(const float beta, const float gama) const
{
	return ((1 - beta - gama) * mesh->u[index0] +
			 beta * mesh->u[index1] +
			 gama * mesh->u[index2]);
}

float MeshTriangle::InterpolateV(const float beta, const float gama) const
{
	return ((1 - beta - gama) * mesh->v[index0] +
		     beta * mesh->v[index1] +
		     gama * mesh->v[index2]);
}
