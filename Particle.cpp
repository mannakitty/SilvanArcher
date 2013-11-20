#include "Particle.h"


Particle::Particle(void)
{
}


Particle::~Particle(void)
{
}

void Particle::Update(float dt)
{
	// Position moving based on velocity and random number
	m_position += (m_velocity*(rand()%8/2))*dt;

	// Rotation of image
	m_angle += (m_angularVelocity*(rand()%8/2))*dt;

	// Life decreasing on each iteration
	m_fLife -= 0.05f * dt;

	// if outside of bounds then reset particle

	if (m_position.x > 40.5 || m_position.x < 39.5 || m_position.y > 1 || m_position.z > 61.5 || m_position.z < 60.5){
		m_position.x = 40;
		m_position.y = -1.31;
		m_position.z = 61;
		m_fLife = (((rand()%10+1)))/10.0f;
	}

	if(m_position.y > 0.75 && (m_position.x > 40.15 || m_position.x < 39.85 || m_position.z > 61.15 || m_position.z < 60.85)){
		m_position.x = 40;
		m_position.y = -1.31;
		m_position.z = 61;
		m_fLife = (((rand()%10+1)))/10.0f;
	}

}

bool Particle::IsAlive()
{
	if (m_fLife > 0)
		return true;
	else
		return false;
}


bool Particle::Initialise(MVector3f pIn, float widthIn, float heightIn, ColourSequence colourSeqIn)
{
	// Set the initial position and velocity
	m_position = pIn;
	m_position.x = m_position.x + ((rand()%2)-(rand()%2));

	// Give the particle some random velocity in the xz plane
	float r1 = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007);
	float r2 = ((((((5) * rand()%11) + 5)) * rand()%11) + 1) * 0.02;
	float r3 = (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007) - (((((((2) * rand()%11) + 1)) * rand()%11) + 1) * 0.007);
	m_velocity = MVector3f(r1, r2, r3);	
	m_velocity.Normalize();
	//m_velocity *= 0.01f; // Speed (m/s)

	// Set the sprite colour sequence, width, height
	m_colourSequence = colourSeqIn;
	m_fWidth = widthIn;
	m_fHeight = heightIn;

	// Set the sprite image intial rotation angle and rotational velocity
	m_angle = 0;
	m_angularVelocity = 0.1f;

	// Set the particle life
	m_fLife = (((rand()%10+1)))/10.0f;

	return true;
}


void Particle::Render(MVector3f lookAt, MVector3f upVector)
{

	if (m_fLife <= 0.0f){
		m_fLife = (((rand()%10+1)))/10.0f;
		m_position.x = 40;
		m_position.y = -1.31;
		m_position.z = 61;
		return;
	}

	// Form a quad at p in the plane orthogonal to the lookAt vector
	lookAt.Normalize();
	MVector3f xAxis = lookAt % upVector;
	xAxis.Normalize();
	MVector3f yAxis = upVector;
	yAxis.Normalize();

	// Find the vertex positions of the quad
	MVector3f p1 = m_position - m_fWidth*xAxis - m_fHeight*yAxis;
	MVector3f p2 = m_position + m_fWidth*xAxis - m_fHeight*yAxis;
	MVector3f p3 = m_position + m_fWidth*xAxis + m_fHeight*yAxis;
	MVector3f p4 = m_position - m_fWidth*xAxis + m_fHeight*yAxis;

	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	int i = (int) floor((1-m_fLife) * m_colourSequence.m_colourSequence.size());
	MVector3f colour = m_colourSequence.m_colourSequence[i];

	glDisable(GL_LIGHTING);
	glPushMatrix();
		// Translate to origin, rotate about the lookAt vector, and translate back -- remember rotations are about the origin
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_angle, lookAt.x, lookAt.y, lookAt.z);
		glTranslatef(-m_position.x, -m_position.y, -m_position.z);

		// Draw a textured quad with the current frame
		glColor4f(colour.x, colour.y, colour.z, m_fLife);
		glBegin(GL_QUADS);		
			glTexCoord2f(0, 0); 
			glVertex3f(p1.x, p1.y, p1.z);
			glTexCoord2f(1, 0); 
			glVertex3f(p2.x, p2.y, p2.z);
			glTexCoord2f(1, 1); 
			glVertex3f(p3.x, p3.y, p3.z);
			glTexCoord2f(0, 1); 
			glVertex3f(p4.x, p4.y, p4.z);
		glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);

	

}
