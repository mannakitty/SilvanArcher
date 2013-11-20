#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library
#include "MVector3f.h"
#include "MGLTexture.h"
#include "ColourSequence.h"

// class that represents a particle in ga,e

class Particle
{
public:
	// constructor
	Particle();
	// deconstructor
	~Particle();
	// initialises particle
	bool Initialise(MVector3f pIn, float widthIn, float heightIn, ColourSequence colourSeqIn);
	// renders particle
	void Render(MVector3f lookAt, MVector3f upVector);
	// updates particle
	void Update(float dt);
	// returns if the particle is still alive or not
	bool IsAlive();

private:
	// length particle is active
	float m_fLife;
	// position of particle
	MVector3f m_position;
	// velocity of particle
	MVector3f m_velocity;

	// width and heigh of particle
	float m_fWidth;
	float m_fHeight;

	// angle and angluar velocity of particle
	float m_angle;
	float m_angularVelocity;

	// colour sequence for particle to go through
	ColourSequence m_colourSequence;

};
