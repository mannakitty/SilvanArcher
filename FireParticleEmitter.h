#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library
#include "MVector3f.h"
#include "MGLTexture.h"
#include "ColourSequence.h"
#include "Particle.h"

// class to reoresent the fire particle emitter used to represent the flames of the camp fire in game

class FireParticleEmitter
{

public:
	// constructor
	FireParticleEmitter();
	// deconstructor
	~FireParticleEmitter();
	// initialise method
	void Initialise(MVector3f fireStart, MVector3f fireDirection, int numTotalParticles, float width, float height);
	// update particles method
	void UpdateParticles(float dt);
	// render paricles
	void Render(MVector3f viewVector, MVector3f upVector);
	// load texture needed fpr particles
	void LoadTexture(char *filename);
	// is the emmiter active
	bool IsActive();

private:
	// stores texture
	MGLTexture m_tex;
	// stores particles
	std::vector<Particle> m_particles;
	// number of particles alive
	int m_numAlive;
	// stores position where particles are emmited and what direction they are heading in
	MVector3f m_start, m_direction;
	// width and height of particles
	float m_width, m_height;
	// total number of particles
	int m_numTotalParticles;
	// is the emmiter active
	bool m_active;

	// clear the emmiter
	void Clear();
	// add a new particle
	void AddParticle();
};

