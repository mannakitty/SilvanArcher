#pragma once
#include <windows.h>
#include "BasicMesh.h"
#include "MVector3f.h"
#include "MCamera.h"
#include "MModel_3DS.h"
#include "MHeightMapTerrain.h"
#include "./include/glut.h"

// Class to represent tree in game

class Tree : public BasicMesh
{
public:
	// Constructor
	Tree();
	Tree(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructor
	~Tree();
	// render mesh to screen
	void Render();
private:
	// Stores position of tree
	MVector3f m_position;
	// Stores model
	MModel_3DS m_mesh;
};

