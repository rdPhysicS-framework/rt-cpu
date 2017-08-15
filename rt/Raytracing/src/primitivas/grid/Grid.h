#ifndef	 __GRID_H__
#define	 __GRID_H__

#include "..\compound\Compound.h"

class Mesh;

enum TriangleType
{
	FLAT,
	SMOOTH
};

class Grid : public Compound
{
private:
	std::vector<Primitive*> cells;
	int nx, ny, nz;
	Mesh *mesh;
	bool reverseNormal;

	RT::Vec3f MinCoordinates();
	RT::Vec3f MaxCoordinates();
	void ComputeMeshNormals();
	void ReadPlyFile(char *fileName, const TriangleType type);

public:
	Grid();
	Grid(Mesh *mesh);
	Grid(const Grid &other);
	~Grid();

	void ReadFlatTriangles(char *filename);
	void ReadSmoothTriangles(char *filename);

	void ReverseMeshNormals();
	void StoreMaterial(AbsMaterial *material, const int index);

	void SetupCells();
	virtual bool Intersect(Ray &ray, float &distance,
						   Result &result);
};

#endif //__GRID_H__