#pragma once
#include "MTexture.h"
#include "MHeightMapTerrain.h"
#include "BasicItem.h"

// Class respresents logs in game

class Log : public BasicItem
{
public:
	// Constructors
	Log(void);
	Log(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructor
	~Log(void);
	// Render methid for log
	void Render();
private:
	// Strores the position of log
	MVector3f m_vPosition;
	// Textures of logs
	GLuint logTexture;
	GLuint logEndTexture;
};

