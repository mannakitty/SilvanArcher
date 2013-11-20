#pragma once
#include "MHeightMapTerrain.h"
#include "MTexture.h"
#include "BasicItem.h"

// Class to represent a barrel in game, this will explode and be removed from game when hit

class Barrel : public BasicItem
{
public:
	// Constructors
	Barrel(void);
	Barrel(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructors
	~Barrel(void);
	// Render method
	void Render();
	// Collision reaction with arrows
	bool collisionReaction(void);
	// Returns position
	MVector3f getPosition();
	// Sets the velocity of the barrel
	void setVelocity(MVector3f speed);
	// Updates the barrels position based on velocity
	void update(float dt, MHeightMapTerrain &g);
private:
	// Sote position of barrel
	MVector3f m_vPosition;
	// Store texture of barrel
	GLuint logTexture;
	// velocity of barrel
	MVector3f m_velocity;
	// resistence on ground
	MVector3f resistance;
};

