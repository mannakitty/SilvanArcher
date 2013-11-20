#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include "MTexture.h"
#include "MVector3f.h"
#include <vector>

// Cross fade example taken from example given around week 5

class MCrossFade
{
public:
	// Constructor
	MCrossFade();
	// Deconstructor
	~MCrossFade();
	// Methid to activate cross fade effect
	void Activate();
	// Redner crossfade effect to screen taking in variables to act as RBG values
	void Render(float red, float green, float blue);
	// Update effect depending on time so that effect fades out over time
	void Update(float dt);
private:
	// Change veiw to do orthigraphic to do effect
	void SetOrthographicProjection();
	// Change view back
	void RestorePerspectiveProjection();
	GLint m_viewport[4];

	// if effect active or not
	bool m_active;
	// how much time elapsed since effect started
	float m_elapsedTime;
	int m_frame;
	int m_totalFrames;

	
};