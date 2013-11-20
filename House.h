#pragma once
#include "MVector3f.h"
#include "MTexture.h"
#include "MHeightMapTerrain.h"
#include "BasicItem.h"

// Class to represent a house

class House : public BasicItem
{
public:
	// Constructors
	House(void);
	House(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructors
	~House(void);
	// Method to render house to screen
	void Render();
private:
	// Stores position of the house
	MVector3f m_vPosition;
	// Textures for house
	GLuint textureBuilding;
	GLuint textureRoof;
};

