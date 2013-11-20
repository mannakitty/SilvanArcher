#pragma once
#include "basicmesh.h"
#include "MHeightMapTerrain.h"

// Class to represent a dead tree in game

class DeadTree : public BasicMesh
{
public:
	// Constructors
	DeadTree(void);
	DeadTree(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// deconstructors
	~DeadTree(void);
	// render dead tree to screen
	void Render();
private:
	// stores position of dead tree
	MVector3f m_position;
	// Stores mesh of dead tree
	MModel_3DS m_mesh;
};

