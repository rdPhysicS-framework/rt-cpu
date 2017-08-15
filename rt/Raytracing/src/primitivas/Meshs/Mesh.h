#ifndef	 __MESH_H__
#define	 __MESH_H__

#include <vector>
#include <RTmath.h>

class Mesh
{
public:
	std::vector<RT::Vec3f> vertices;
	std::vector<RT::Vec3f> normals;
	std::vector<unsigned int> indices;
	std::vector<std::vector<int>> vertexFaces;
	std::vector<float> u;
	std::vector<float> v;
	int numVertices;
	int numTriangles;

public:
	Mesh();
	Mesh(const Mesh &other);


};

#endif //__MESH_H__
