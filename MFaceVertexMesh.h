#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library
#include <vector>
#include "MVector3f.h"
#include "MVertex.h"


typedef struct {
	std::vector<unsigned int> id;	// list of triangle IDs 
} MTriangleList;

class MFaceVertexMesh
{
public:
	MFaceVertexMesh();
	~MFaceVertexMesh();
	void Render();
	bool CreateFromTriangleList(const std::vector<MVertex> &vertices, const std::vector<unsigned int> &triangles);
	void ComputeVertexNormals();
	MVector3f ComputeTriangleNormal(unsigned int tId);
	void ComputeTextureCoordsXZ(float xScale, float zScale);


private:
	std::vector<MVertex> m_vertices;			// A list of vertices
	std::vector<unsigned int> m_triangles;		// Stores vertex IDs -- every three makes a triangle
	std::vector<MTriangleList> m_onTriangle;	// For each vertex, stores a list of triangle IDs saying which triangles the vertex is on

};