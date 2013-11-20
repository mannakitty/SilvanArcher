#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glut.h"											// Header File For The OpenGL32 Library
#include "MVector3f.h"

class MBouncingBall
{
public:
	MBouncingBall();
	~MBouncingBall();
	bool Initialise(MVector3f position, MVector3f velocity, MVector3f acceleration, float coefficientOfRestitution, float radius);
	bool UpdatePhysics(float dt);
	bool CollisionDetection(float yPlane);
	void CollisionResponse();
	void Render();

private:
	MVector3f m_position;
	MVector3f m_velocity;
	MVector3f m_acceleration;
	float m_coefficientOfRestitution;
	float m_radius;
	bool m_active;

	
};