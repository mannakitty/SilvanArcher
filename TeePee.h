#pragma once
#include "MHeightMapTerrain.h"
#include "MTexture.h"
#include "BasicItem.h"
#include ".\include\gl.h"

// Class which represents a teepee/tent in game

class TeePee : public BasicItem
{
public:
	// Constructors
	TeePee(void);
	TeePee(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructors
	~TeePee(void);
	// Method to render tent to screen
	void Render (void);
private:
	// Sote position of barrel
	MVector3f m_vPosition;
	// Store texture of barrel
	GLuint canvasTexture;
};

