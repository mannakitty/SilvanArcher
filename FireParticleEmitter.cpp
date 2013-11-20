#pragma once
#include "FireParticleEmitter.h"
#include "ColourSequence.h"

FireParticleEmitter::FireParticleEmitter()
{
	m_active = false;
}


FireParticleEmitter::~FireParticleEmitter()
{}

void FireParticleEmitter::LoadTexture(char *filename)
{
	// Load the texture
	m_tex.Load((char *)filename); // Loads an image.  Make sure the image is in a 32 bit format (tga) with transparency


}

bool FireParticleEmitter::IsActive()
{
	return m_active;
}

void FireParticleEmitter::Initialise(MVector3f fireStart, MVector3f fireDirection, int numTotalParticles, float width, float height)
{
	// We're going to launch a set of particles along a ray that starts at smokeTrailStart and is directed along smokeTrailDirection
	m_start = fireStart;
	m_direction = fireDirection;
	m_direction.Normalize();
	m_direction *= 2.0f;

	m_width = width;
	m_height = height;

	m_numTotalParticles = numTotalParticles;
	m_active = true;
	for(int i = 0; i <= numTotalParticles; i++){
		AddParticle();
	}
}

void FireParticleEmitter::Clear()
{
	//remove particles
	m_particles.clear();
	m_active = false;
}

void FireParticleEmitter::Render(MVector3f viewVector, MVector3f upVector)
{
	//m_tex.Use();				// Binds the bitmap for use

	// Render each particle
	for (unsigned int i = 0; i < m_particles.size(); i++) 
		m_particles[i].Render(viewVector, upVector);
	
	
}

void FireParticleEmitter::UpdateParticles(float dt)
{

	static float accumulatedTime = 0.0f;

	m_numAlive = 0;
	for (unsigned int i = 0; i < m_particles.size(); i++) {
		m_particles[i].Update(dt);
		// Count the number of alive particles
		if (m_particles[i].IsAlive())
			m_numAlive++;

	}

	accumulatedTime += dt;

	// Check if there are no more alive particles -- if so, clear
	if (m_active && m_particles.size() > 0 && m_numAlive == 0) {
		Clear();
		return;
	}

	
	// Add a particle every 100 ms, up to the total number of particles to be added
	if (accumulatedTime > 0.1f && m_particles.size() < (unsigned int) m_numTotalParticles) {
		AddParticle();
		accumulatedTime -= 0.1f;
	}

		


}
		
// Add another particle 
void FireParticleEmitter::AddParticle()
{

	ColourSequence colourSeq;
	colourSeq.RedToYellowFast(10);
	Particle particle;
	MVector3f p = m_start + (float) m_particles.size() * m_direction;
	particle.Initialise(p, m_width, m_height, colourSeq);
	m_particles.push_back(particle);

}



