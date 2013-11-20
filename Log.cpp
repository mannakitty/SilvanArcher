#include "Log.h"
#include <math.h>
#include ".\include\glut.h"	


Log::Log(void)
{
}

Log::Log(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Store x and z positions
	m_vPosition.x = x;
	m_vPosition.z = z;
	// Get y position and store it
	float y = g_heightMapTerrain.ReturnGroundHeight(m_vPosition);
	m_vPosition.y = y + 1;
	// Set the textures
	MTexture texture;
	texture.CreateFromBMP(&logTexture, "Resources/Textures/bark.bmp");
	texture.CreateFromBMP(&logEndTexture, "Resources/Textures/Wood.bmp");
	MVector3f temp = m_vPosition;
	temp.x += 2.5;
	// setup boundingbox 
	MVector3f minPoint(2.5f, 1.0f, 1.0f);
	minPoint = temp - minPoint;
	MVector3f maxPoint(2.5f, 1.0f, 1.0f);
	maxPoint = temp + maxPoint;
	bBox.Set(minPoint, maxPoint);
	objectMass = 50;
}


Log::~Log(void)
{
}

void Log::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_vPosition.x, m_vPosition.y, m_vPosition.z);
		// Rotate so sideways
		glRotatef(90, 0, 1, 0);
		// Create a quadric to use in creating cylinder	
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		// Sort out texture
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, logTexture);
		gluQuadricTexture(quadratic, GL_TRUE);
		// Draw cylinder
		gluCylinder(quadratic,1.0f,1.0f,5.0f,32,32);
		
		// Add ends to cylinder
		glPushMatrix();
			GLUquadricObj *quadratic2 = gluNewQuadric();
			glRotatef(90, 0, 0, 1);
			glRotatef(180, 0, 1, 0);
			// Bind new texture
			glBindTexture(GL_TEXTURE_2D, logEndTexture);
			gluQuadricTexture(quadratic2, GL_TRUE);
			// Draw disk/circle
			gluDisk(quadratic2, 0.0f, 1.0f, 32,32);
		glPopMatrix();

		glPushMatrix();
			// Move into position
			glTranslatef(0,0,5);
			GLUquadricObj *quadratic3 = gluNewQuadric();
			glRotatef(90, 0, 0, 1);
			// Bind new texture
			glBindTexture(GL_TEXTURE_2D, logEndTexture);
			gluQuadricTexture(quadratic3, GL_TRUE);
			// Draw disc/circle
			gluDisk(quadratic3, 0.0f, 1.0f, 32,32);
		glPopMatrix();

	glPopMatrix();
}
