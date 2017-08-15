#include "Grid.h"
#include "..\..\raytracer\Ray.h"
#include "..\Result.h"
#include "..\..\Util\BBox.h"
#include "..\..\Util\Util.h"
#include "..\Meshs\Mesh.h"
#include "..\..\Util\ply.h"
#include "..\Meshs\FlatMeshTriangle.h"
#include "..\Meshs\SmoothMeshTriangle.h"

Grid::Grid() :
	Compound(),
	nx(0),
	ny(0),
	nz(0),
	mesh(new Mesh),
	reverseNormal(false)
{}

Grid::Grid(Mesh *mesh) :
	Compound(),
	nx(0),
	ny(0),
	nz(0),
	mesh(mesh),
	reverseNormal(false)
{
}

Grid::Grid(const Grid &other) :
	Compound(other),
	nx(other.nx),
	ny(other.ny),
	nz(other.nz),
	mesh(other.mesh),
	reverseNormal(other.reverseNormal)
{}

Grid::~Grid()
{
	if (mesh)
		delete mesh;
	/*for (Primitive *p : cells)
		delete p;
	cells.clear();*/
}

void Grid::ReadFlatTriangles(char * filename)
{
	ReadPlyFile(filename, FLAT);
}

void Grid::ReadSmoothTriangles(char * filename)
{
	ReadPlyFile(filename, SMOOTH);
	ComputeMeshNormals();
}

void Grid::ReverseMeshNormals()
{
	reverseNormal = true;
}

void Grid::StoreMaterial(AbsMaterial *material, const int index)
{
	objects[index]->SetMaterial(material);
}

void Grid::SetupCells()
{
	RT::Vec3f p0 = MinCoordinates();
	RT::Vec3f p1 = MaxCoordinates();

	bbox.x0 = p0.x; 
	bbox.y0 = p0.y; 
	bbox.z0 = p0.z;

	bbox.x1 = p1.x; 
	bbox.y1 = p1.y; 
	bbox.z1 = p1.z;

	int numObjects = objects.size();

	double wx = p1.x - p0.x;
	double wy = p1.y - p0.y;
	double wz = p1.z - p0.z;

	double multiplier = 2.0;

	double s = pow(wx * wy * wz / numObjects, 0.3333333);
	nx = multiplier * wx / s + 1;
	ny = multiplier * wy / s + 1;
	nz = multiplier * wz / s + 1;

	int numCells = nx * ny * nz;
	cells.reserve(numObjects);

	for (int i = 0; i < numCells; i++)
		cells.push_back(nullptr);

	std::vector<int> counts;
	counts.reserve(numCells);

	for (int i = 0; i < numCells; i++)
		counts.push_back(0);

	BBox objBox;
	int index;

	for (int i = 0; i < numObjects; i++)
	{
		objBox = objects[i]->GetBoundingBox();

		int ixmin = clamp((objBox.x0 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymin = clamp((objBox.y0 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmin = clamp((objBox.z0 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

		int ixmax = clamp((objBox.x1 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymax = clamp((objBox.y1 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmax = clamp((objBox.z1 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

		for (int iz = izmin; iz <= izmax; iz++)
			for (int iy = iymin; iy <= iymax; iy++)
				for (int ix = ixmin; ix <= ixmax; ix++) 
				{
					index = ix + nx * iy + nx * ny * iz;

					if (counts[index] == 0)
					{
						cells[index] = objects[i];
						counts[index] += 1;
					}
					else
					{
						if (counts[index] == 1)
						{
							Compound *compound = new Compound();
							compound->AddObject(cells[index]);
							compound->AddObject(objects[i]);

							cells[index] = compound;
							counts[index] += 1;
						}
						else
						{
							cells[index]->AddObject(objects[i]);
							counts[index] += 1;
						}
					}
				}
	}

	objects.clear();
	counts.clear();
}

bool Grid::Intersect(Ray &ray, float &distance, Result &result)
{
	double ox = ray.GetOrigin().x;
	double oy = ray.GetOrigin().y;
	double oz = ray.GetOrigin().z;
	double dx = ray.GetDirection().x;
	double dy = ray.GetDirection().y;
	double dz = ray.GetDirection().z;

	double x0 = bbox.x0;
	double y0 = bbox.y0;
	double z0 = bbox.z0;
	double x1 = bbox.x1;
	double y1 = bbox.y1;
	double z1 = bbox.z1;

	double txmin, tymin, tzmin;
	double txmax, tymax, tzmax;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		txmin = (x0 - ox) * a;
		txmax = (x1 - ox) * a;
	}
	else
	{
		txmin = (x1 - ox) * a;
		txmax = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		tymin = (y0 - oy) * b;
		tymax = (y1 - oy) * b;
	}
	else
	{
		tymin = (y1 - oy) * b;
		tymax = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tzmin = (z0 - oz) * c;
		tzmax = (z1 - oz) * c;
	}
	else
	{
		tzmin = (z1 - oz) * c;
		tzmax = (z0 - oz) * c;
	}

	double t0, t1;

	if (txmin > tymin)
		t0 = txmin;
	else
		t0 = tymin;

	if (tzmin > t0)
		t0 = tzmin;

	if (txmax < tymax)
		t1 = txmax;
	else
		t1 = tymax;

	if (tzmax < t1)
		t1 = tzmax;

	if (t0 > t1)
		return false;

	int ix, iy, iz;

	if (bbox.Inside(ray.GetOrigin()))
	{
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else
	{
		RT::Vec3f p = ray.IntersectionPoint(t0);//ray.GetOrigin() + t0 * ray.GetDirection();
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}

	double dtx = (txmax - txmin) / nx;
	double dty = (tymax - tymin) / ny;
	double dtz = (tzmax - tzmin) / nz;

	double txnext, tynext, tznext;
	int ixstep, iystep, izstep;
	int ixstop, iystop, izstop;

	/*txnext = txmin + (ix + 1) * dtx;
	ixstep = +1;
	ixstop = nx;

	tynext = tymin + (iy + 1) * dty;
	iystep = +1;
	iystop = ny;

	tznext = tzmin + (iz + 1) * dtz;
	izstep = +1;
	izstop = nz;*/

	if (dx > 0)
	{
		txnext = txmin + (ix + 1) * dtx;
		ixstep = +1;
		ixstop = nx;
	}
	else
	{
		txnext = txmin + (nx - ix) * dtx;
		ixstep = -1;
		ixstop = -1;
	}

	if (dx == 0.0)
	{
		txnext = INFINITE;
		ixstep = -1;
		ixstop = -1;
	}

	if (dy > 0)
	{
		tynext = tymin + (iy + 1) * dty;
		iystep = +1;
		iystop = ny;
	}
	else
	{
		tynext = tymin + (ny - iy) * dty;
		iystep = -1;
		iystop = -1;
	}

	if (dy == 0.0)
	{
		tynext = INFINITE;
		iystep = -1;
		iystop = -1;
	}

	if (dz > 0)
	{
		tznext = tzmin + (iz + 1) * dtz;
		izstep = +1;
		izstop = nz;
	}
	else
	{
		tznext = tzmin + (nz - iz) * dtz;
		izstep = -1;
		izstop = -1;
	}

	if (dz == 0.0)
	{
		tznext = INFINITE;
		izstep = -1;
		izstop = -1;
	}

	//RT::Vec3f whPoint;

	while (true)
	{
		Primitive *object = cells[ix + nx * iy + nx * ny * iz];

		if (txnext < tynext && txnext < tznext)
		{
			if (object && object->Intersect(ray, distance, result) &&
				distance < txnext)
			{
				//whPoint = ray.IntersectionPoint(distance);
				//normal = object->GetNormalAt(whPoint);
				material = object->GetMaterial();
				return true;
			}

			txnext += dtx;
			ix += ixstep;

			if (ix == ixstop)
				return false;
		}
		else
		{
			if (tynext < tznext)
			{
				if (object && object->Intersect(ray, distance, result) &&
					distance < tynext)
				{
					//whPoint = ray.IntersectionPoint(distance);
					//normal = object->GetNormalAt(whPoint);
					material = object->GetMaterial();
					return true;
				}


				tynext += dty;
				iy += iystep;

				if (iy == iystop)
					return false;
			}
			else
			{
				if (object && object->Intersect(ray, distance, result) &&
					distance < tznext)
				{
					//whPoint = ray.IntersectionPoint(distance);
					//normal = object->GetNormalAt(whPoint);
					material = object->GetMaterial();
					return true;
				}
				
				tznext += dtz;
				iz += izstep;

				if (iz == izstop)
					return false;
			}
		}
	}
}

RT::Vec3f Grid::MinCoordinates()
{
	BBox objBox;
	RT::Vec3f p0(INFINITE, INFINITE, INFINITE);

	//int numObjects = objects.size();

	for (Primitive *obj : objects)
	{
		objBox = obj->GetBoundingBox();

		if (objBox.x0 < p0.x)
			p0.x = objBox.x0;
		if (objBox.y0 < p0.y)
			p0.y = objBox.y0;
		if (objBox.z0 < p0.z)
			p0.z = objBox.z0;
	}

	p0.x -= EPSILON;
	p0.y -= EPSILON;
	p0.z -= EPSILON;

	return p0;
}

RT::Vec3f Grid::MaxCoordinates()
{
	BBox objBox;
	RT::Vec3f p1(-INFINITE, -INFINITE, -INFINITE);

	//int numObjects = objects.size();

	for (Primitive *obj : objects)
	{
		objBox = obj->GetBoundingBox();

		if (objBox.x1 > p1.x)
			p1.x = objBox.x1;
		if (objBox.y1 > p1.y)
			p1.y = objBox.y1;
		if (objBox.z1 > p1.z)
			p1.z = objBox.z1;
	}

	p1.x += EPSILON;
	p1.y += EPSILON;
	p1.z += EPSILON;

	return p1;
}

void Grid::ComputeMeshNormals()
{
	mesh->normals.reserve(mesh->numVertices);

	for (int i = 0; i < mesh->numVertices; i++)
	{
		RT::Vec3f n;

		int vfSize = mesh->vertexFaces[i].size();
		for (int j = 0; j < vfSize; j++)
		{
			n += objects[mesh->vertexFaces[i][j]]->GetNormalAt(RT::Vec3f());
		}

		if (n.x == 0.0 && n.y == 0.0 && n.z == 0.0)
			n.y = 1.0f;
		else
			n.Normalize();

		mesh->normals.push_back(n);
	}

	for (int i = 0; i < mesh->numVertices; i++)
	{
		int vfSize = mesh->vertexFaces[i].size();
		for (int j = 0; j < vfSize; j++)
			mesh->vertexFaces[i].clear();
	}

	mesh->vertexFaces.clear();
}

void Grid::ReadPlyFile(char *fileName, const TriangleType type)
{
	typedef struct Vertex
	{
		float x, y, z;
	} Vertex;

	typedef struct Face 
	{
		unsigned char nverts;    
		int* verts;              
	} Face;

	PlyProperty vertProps[] = {
		{ "x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0 },
		{ "y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0 },
		{ "z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0 }
	};

	PlyProperty faceProps[] = {
		{ "vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts) }
	};

	//int i, j;
	PlyFile* ply;
	int nelems;
	char** elist;
	int fileType;
	float version;
	int nprops;
	int numElems;
	PlyProperty** plist;
	Vertex** vlist;
	Face** flist;
	char* elemName;
	int numComments;
	char** comments;
	int numObjInfo;
	char** objInfo;

	ply = ply_open_for_reading(fileName, &nelems, &elist, &fileType, &version);

	printf("version %f\n", version);
	printf("type %d\n", fileType);

	for (int i = 0; i < nelems; i++)
	{
		elemName = elist[i];
		plist = ply_get_element_description(ply, elemName, &numElems, &nprops);

		std::cout << "element name " << elemName << " num elements = " << numElems
				  << " num properties = " << nprops << std::endl;

		if (equal_strings("vertex", elemName))
		{
			ply_get_property(ply, elemName, &vertProps[0]);
			ply_get_property(ply, elemName, &vertProps[1]);
			ply_get_property(ply, elemName, &vertProps[2]);

			mesh->numVertices = numElems;
			mesh->vertices.reserve(numElems);

			for (int j = 0; j < numElems; j++)
			{
				Vertex *vertex = new Vertex;

				ply_get_element(ply, (void*)vertex);
				mesh->vertices.push_back(RT::Vec3f(vertex->x, vertex->y, vertex->z));
				delete vertex;
			}
		}

		if (equal_strings("face", elemName))
		{
			ply_get_property(ply, elemName, &faceProps[0]);

			mesh->numTriangles = numElems;
			objects.reserve(numElems);

			mesh->vertexFaces.reserve(mesh->numVertices);
			std::vector<int> facesList;

			for (int j = 0; j < numElems; j++)
				mesh->vertexFaces.push_back(facesList);

			int count = 0;
			
			for (int j = 0; j < numElems; j++)
			{
				Face* face = new Face;

				ply_get_element(ply, (void*)face);

				if (type == FLAT)
				{
					FlatMeshTriangle *triangle = new FlatMeshTriangle(mesh, face->verts[0],
															 face->verts[1], face->verts[2]);
					triangle->ComputeNormal(reverseNormal);
					objects.push_back(triangle);
				}

				if (type == SMOOTH)
				{
					SmoothMeshTriangle *triangle = new SmoothMeshTriangle(mesh, face->verts[0],
																 face->verts[1], face->verts[2]);
					triangle->ComputeNormal(reverseNormal);
					objects.push_back(triangle);

					mesh->vertexFaces[face->verts[0]].push_back(count);
					mesh->vertexFaces[face->verts[1]].push_back(count);
					mesh->vertexFaces[face->verts[2]].push_back(count);
					count++;
				}
			}

			if (type == FLAT)
				mesh->vertexFaces.clear();
		}

		for (int j = 0; j < nprops; j++)
			printf("property %s\n", plist[j]->name);
	}

	comments = ply_get_comments(ply, &numComments);

	for (int i = 0; i < numComments; i++)
		printf("comment = '%s'\n", comments[i]);

	objInfo = ply_get_obj_info(ply, &numObjInfo);

	for (int i = 0; i < numObjInfo; i++)
		printf("objInfo = '%s'\n", objInfo[i]);

	ply_close(ply);
}

