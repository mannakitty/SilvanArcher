#pragma once
#include "BasicMesh.h"
#include <windows.h>
#include "MVector3f.h"
#include "MCamera.h"
#include "MModel_3DS.h"
#include "./include/glut.h"

// class to represent fire arrow pick up

class FireArrow : public BasicMesh
{
public:
	// constructor
	FireArrow(void);
	FireArrow(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// deconstructor
	~FireArrow(void);
	// render method
	void Render();
private:
	// position of fire arrow
	MVector3f m_position;
	// Stores mesh of fire arrow
	MModel_3DS m_mesh;
};

