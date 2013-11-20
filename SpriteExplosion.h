#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"								// Header File For The OpenGL32 Library
#include "MVector3f.h"
#include "MGLTexture.h"

// class to represent sprite explosions in game

class SpriteExplosion
{
public:
	// constructor
	SpriteExplosion(MVector3f p);
	// deconstructor
	~SpriteExplosion();
	// initailse method for explosion
	bool Initialise(const char *filename, const int frameWidth, const int frameHeight, const int numFrames);
	// update method
	void Update(float dt);
	// render method
	void Render(MVector3f lookAt, MVector3f upVector, float width, float height);
	// activates sprite explosion
	void Activate();

private:
	// is explosion active or not
	bool m_active;
	// which frame explosion is om
	unsigned int m_frame;
	// total nu,ber of frames
	unsigned int m_totalFrames;
	// total time elapsed
	float m_elapsedTime;

	// frame width and height
	unsigned int m_frameWidth;
	unsigned int m_frameHeight;

	unsigned int m_framesX;
	unsigned int m_framesY;

	// position of explosion
	MVector3f position;
	// texture for explosion
	MGLTexture tex;

};
