#pragma once
#include "MHeightMapTerrain.h"
#include "Log.h"
#include "BasicItem.h"

// This creates the logs for the camp fire.  The light is set in MLightingEffects

class CampFire : public BasicItem
{
public:
	// Constructor
	CampFire(void);
	CampFire(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstuctor
	~CampFire(void);
	// Method to render house to screen
	void Render();
private:
	// Stores position of the house
	MVector3f m_vPosition;
	// Textures for house
	GLuint textureLog;
};

