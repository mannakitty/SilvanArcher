#pragma once
#include "Barrel.h"

// Barrel class

Barrel::Barrel(void)
{
}

Barrel::Barrel(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_vPosition.x = (float)x;
	m_vPosition.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_vPosition);
	m_vPosition.y = y + (float)1.5;
	// Set texture 
	MTexture texture;
	texture.CreateFromBMP(&logTexture, "Resources/Textures/light--floorboard-wood.bmp");
	// setup boundingbox 
	MVector3f minPoint(0.5f, 1.5f, 0.5f);
	minPoint = m_vPosition - minPoint;
	MVector3f maxPoint(0.5f, 0.0f, 0.5f);
	maxPoint = m_vPosition + maxPoint;
	bBox.Set(minPoint, maxPoint);
	// set velocity
	m_velocity = MVector3f(0.0f, 0.0f, 0.0f);
	// set resistence
	resistance = MVector3f(0.9f, 0.0f, 0.9f);
	// set object mass
	objectMass = 30;
}

Barrel::~Barrel(void)
{
}

void Barrel::Render(void)
{
	
	glPushMatrix();
		// Move to want position
		glTranslatef(m_vPosition.x, m_vPosition.y, m_vPosition.z);
		// Rotate 90 degrees in x axis so cylinder upright
		glRotatef(90, 1, 0, 0);			
		// Create quadric for making cylinder
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		// Sort out texture and colour
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, logTexture);
		gluQuadricTexture(quadratic, GL_TRUE);
		// Draw a cylinder
		gluCylinder(quadratic,0.5f,0.5f,1.5f,32,32);
		
		// Draw ends of cylinder with texture
		glPushMatrix();
			GLUquadricObj *quadratic2 = gluNewQuadric();
			// Rotate into position
			glRotatef(90, 0, 0, 1);
			glRotatef(180, 0, 1, 0);
			// Add texture
			glBindTexture(GL_TEXTURE_2D, logTexture);
			gluQuadricTexture(quadratic2, GL_TRUE);
			// Draw circle
			gluDisk(quadratic2, 0.0f, 0.5f, 32,32);
		glPopMatrix();

		glPushMatrix();
		// Move into position
			glTranslatef(0,0,1.5);
			GLUquadricObj *quadratic3 = gluNewQuadric();
			glRotatef(90, 0, 0, 1);
			// Add texture
			glBindTexture(GL_TEXTURE_2D, logTexture);
			gluQuadricTexture(quadratic3, GL_TRUE);
			// Draw circle
			gluDisk(quadratic3, 0.0f, 1.0f, 32,32);
		glPopMatrix();

	glPopMatrix();
}

bool Barrel::collisionReaction(void)
{
	// returns true
	return true;
}

MVector3f Barrel::getPosition(void)
{
	// returns position
	return m_vPosition;
}

void Barrel::setVelocity(MVector3f speed)
{
	// sets velocity of barrel
	m_velocity = speed * 5;
}

void Barrel::update(float dt,  MHeightMapTerrain &g)
{
	// if x and z of velocity do not equal 0
	if ((m_velocity.x != 0) && (m_velocity.z != 0) ){
		// update velocity
		m_velocity.y = 0;
		m_velocity.x = m_velocity.x * resistance.x;
		m_velocity.z = m_velocity.z * resistance.z;
		
		// sort out y position
		float tempY = m_vPosition.y;

		m_vPosition += m_velocity * dt;
		m_vPosition.y = g.ReturnGroundHeight(m_vPosition) + 1.5;
		
		// update bounding box
		bBox.Translate((m_velocity * dt));
		tempY = (g.ReturnGroundHeight(m_vPosition) + 1.5) - tempY;
		bBox.TranslateY(tempY);

		
		// if velocity is very low set it to 0
		if((m_velocity.x < 0.1 && m_velocity.z < 0.1) && (m_velocity.x > -0.1 && m_velocity.z > -0.1)){
			m_velocity = MVector3f(0.0f, 0.0f, 0.0f);
		}
	}	
}
