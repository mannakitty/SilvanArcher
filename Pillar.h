#pragma once
#include <windows.h>
#include "BasicMesh.h"
#include "MVector3f.h"
#include "MCamera.h"
#include "MModel_3DS.h"
#include "MHeightMapTerrain.h"
#include "./include/glut.h"

// Class to represent pillars in game

class Pillar : public BasicMesh
{
public:
	// Constructor
	Pillar();
	Pillar(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructor
	~Pillar();
	// render pillar to screen
	void Render();
private:
	// stores position of pillar
	MVector3f m_position;
	// Stores mesh of pillar
	MModel_3DS m_mesh;
};

