#include "MBouncingBall.h"

MBouncingBall::MBouncingBall()
{}

MBouncingBall::~MBouncingBall()
{}

bool MBouncingBall::Initialise(MVector3f position, MVector3f velocity, MVector3f acceleration, float coefficientOfResitution, float radius)
{
	m_position = position;
	m_velocity = velocity;
	m_acceleration = acceleration;
	m_coefficientOfRestitution = coefficientOfResitution;
	m_radius = radius;
	m_active = true;
	return true;
}

bool MBouncingBall::CollisionDetection(float yPlane)
{
	if (m_position.y - m_radius < yPlane && m_velocity.y < 0) {
		return true;
	}
	return false;
}

void MBouncingBall::CollisionResponse()
{
	float convergenceThreshold = 0.5f;
	if (m_velocity.Length() > convergenceThreshold)
		m_velocity = MVector3f(m_velocity.x, -m_velocity.y * m_coefficientOfRestitution, m_velocity.z);
	else {
		m_velocity = MVector3f(0, 0, 0);
		m_acceleration = MVector3f(0, 0, 0);
		m_position = MVector3f(m_position.x, m_radius, m_position.z);
		m_active = false;
	}
}

bool MBouncingBall::UpdatePhysics(float dt)
{
	if (m_active == false)
		return false;

	bool bounce = false;

	m_position += m_velocity * dt + 0.5 * (m_acceleration * dt * dt);
	m_velocity += m_acceleration * dt;
	
	float yPlane = 0.0f;
	if(CollisionDetection(yPlane)) {
		CollisionResponse();
		bounce = true;
	}


	return bounce;

}


void MBouncingBall::Render()
{


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glutSolidSphere(m_radius, 15, 15);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

}
