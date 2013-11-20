#pragma once
#include "basicmesh.h"
#include "MHeightMapTerrain.h"

// Class to represent a a heart pick up which increases health

class Heart : public BasicMesh
{
public:
	// Constructors
	Heart(void);
	Heart(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// deconstructors
	~Heart(void);
	// render heart to screen
	void Render();
	// method to react to collisions
	bool collisionReaction();
private:
	// stores position of heart
	MVector3f m_position;
	// Stores mesh of heart
	MModel_3DS m_mesh;
};

