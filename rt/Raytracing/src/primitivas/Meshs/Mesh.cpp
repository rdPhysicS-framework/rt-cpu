#include "Mesh.h"

Mesh::Mesh() :
	numVertices(0),
	numTriangles(0)
{}

Mesh::Mesh(const Mesh &other) :
	vertices(other.vertices),
	normals(other.normals),
	u(other.u),
	v(other.v),
	numVertices(other.numVertices),
	numTriangles(other.numTriangles)
{
}
