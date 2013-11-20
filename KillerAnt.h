#pragma once
#include <windows.h>
#include "BasicMesh.h"
#include "MVector3f.h"
#include "MCamera.h"
#include "MModel_3DS.h"
#include "MHeightMapTerrain.h"
#include "./include/glut.h"

// Class to represent an enemy ant to screen

class KillerAnt : public BasicMesh
{
public:
	// Construtors
	KillerAnt(void);
	KillerAnt(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructors
	~KillerAnt(void);
	// render ant to screen
	void Render(MVector3f me);
	// collision reaction method
	bool collisionReaction();
	// updates position of ant
	void Update(float dt, MVector3f m, MHeightMapTerrain &g_heightMapTerrain);
	// returns position of ant
	MVector3f getPosition();

private:
	// stores position of ant
	MVector3f m_position;
	// stores the direction the to the player
	MVector3f direction;
	// stores the speed at which ants travel
	MVector3f velocity;
	// direction mesh faces
	MVector3f meshDirection;
	// Stores mesh of ant
	MModel_3DS m_mesh;
	// health of ant
	int health;
	// angle of rotation for the ant so that it faces the player
	float angle;
	//
	MBoundingBox defaultBox;
};

