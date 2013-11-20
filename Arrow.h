#pragma once
#include "BasicMesh.h"
#include <windows.h>
#include "MVector3f.h"
#include "MCamera.h"
#include "MModel_3DS.h"
#include "./include/glut.h"

// A class to represent a player projectile in game

class Arrow : public BasicMesh
{
public:
	// Constructors
	Arrow(void);
	Arrow(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructor
	~Arrow();
	// render arrow to screen
	void Render();
	// Launch the arrow from the camera position
	void LaunchFromCamera(MCamera camera);
	// Update the arrows position and velocity
	void Update(float dt);
	// initialise the arrow
	void Initialise();
	// returns the cyrrent position of the arrow
	MVector3f getPosition(void);
private:
	// stores position of spider
	MVector3f m_position;
	// stores velocity of arrow
	MVector3f m_velocity;
	// stores angles needed to rotate arrow to the direction its facing in
	float m_theta;
	float m_phi;
	// vector to represent the force of gravity
	MVector3f gravity;
	// vector to represent the acceleration of the arrow
	MVector3f acceleration;
	// the mass of the arrow
	float mass;

	
	// Stores mesh of spider
	MModel_3DS m_mesh;
};

