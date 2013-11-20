#include "CampFire.h"


CampFire::CampFire(void)
{
}

CampFire::CampFire(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Store x and z positions
	m_vPosition.x = (float)x;
	m_vPosition.z = (float)z;
	// Find high of terrain at coordinate and store
	float y = g_heightMapTerrain.ReturnGroundHeight(m_vPosition);
	m_vPosition.y = y;
	// Store textures
	MTexture texture;
	texture.CreateFromBMP(&textureLog, "Resources/Textures/burned-wood.bmp");
	// setup boundingbox 
	MVector3f minPoint(1.0f, 0.0f, 0.0f);
	minPoint = m_vPosition - minPoint;
	MVector3f maxPoint(1.0f, 0.4f, 2.0f);
	maxPoint = m_vPosition + maxPoint;
	bBox.Set(minPoint, maxPoint);
	objectMass = 45;
}


CampFire::~CampFire(void)
{
}

void CampFire::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_vPosition.x, m_vPosition.y + (float)0.3, m_vPosition.z);
		glPushMatrix();
			// Create a quadric to use in creating cylinder	
			GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			// Sort out texture
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textureLog);
			gluQuadricTexture(quadratic, GL_TRUE);
			// Draw cylinder
			gluCylinder(quadratic,0.1f,0.1f,2.0f,32,32);
		
			// Add ends to cylinder
			glPushMatrix();
				GLUquadricObj *quadratic2 = gluNewQuadric();
				glRotatef(90, 0, 0, 1);
				glRotatef(180, 0, 1, 0);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic2, GL_TRUE);
				// Draw disk/circle
				gluDisk(quadratic2, 0.0f, 0.1f, 32,32);
			glPopMatrix();

			glPushMatrix();
				// Move into position
				glTranslatef(0,0,2);
				GLUquadricObj *quadratic3 = gluNewQuadric();
				glRotatef(90, 0, 0, 1);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic3, GL_TRUE);
				// Draw disc/circle
				gluDisk(quadratic3, 0.0f, 0.1f, 32,32);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		// Move into position
		glTranslatef(m_vPosition.x - 1, m_vPosition.y + (float)0.3, m_vPosition.z + 1);
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
			// Create a quadric to use in creating cylinder	
			quadratic = gluNewQuadric();
			// Sort out texture
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textureLog);
			gluQuadricTexture(quadratic, GL_TRUE);
			// Draw cylinder
			gluCylinder(quadratic,0.1f,0.1f,2.0f,32,32);
		
			// Add ends to cylinder
			glPushMatrix();
				glRotatef(90, 0, 0, 1);
				glRotatef(180, 0, 1, 0);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic2, GL_TRUE);
				// Draw disk/circle
				gluDisk(quadratic2, 0.0f, 0.1f, 32,32);
			glPopMatrix();

			glPushMatrix();
				// Move into position
				glTranslatef(0,0,2);
				glRotatef(90, 0, 0, 1);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic3, GL_TRUE);
				// Draw disc/circle
				gluDisk(quadratic3, 0.0f, 0.1f, 32,32);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		// Move into position
		glTranslatef(m_vPosition.x - (float)0.75, m_vPosition.y + (float)0.3, m_vPosition.z + (float)0.4);
		glRotatef(45, 0, 1, 0);
		glPushMatrix();
			// Sort out texture
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textureLog);
			gluQuadricTexture(quadratic, GL_TRUE);
			// Draw cylinder
			gluCylinder(quadratic,0.1f,0.1f,2.0f,32,32);
		
			// Add ends to cylinder
			glPushMatrix();
				glRotatef(90, 0, 0, 1);
				glRotatef(180, 0, 1, 0);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic2, GL_TRUE);
				// Draw disk/circle
				gluDisk(quadratic2, 0.0f, 0.1f, 32,32);
			glPopMatrix();

			glPushMatrix();
				// Move into position
				glTranslatef(0,0,2);
				glRotatef(90, 0, 0, 1);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic3, GL_TRUE);
				// Draw disc/circle
				gluDisk(quadratic3, 0.0f, 0.1f, 32,32);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		// Move into position
		glTranslatef(m_vPosition.x - (float)0.75, m_vPosition.y + (float)0.3, m_vPosition.z + (float)1.6);
		glRotatef(135, 0, 1, 0);
		glPushMatrix();
			// Sort out texture
			glColor3f(1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, textureLog);
			gluQuadricTexture(quadratic, GL_TRUE);
			// Draw cylinder
			gluCylinder(quadratic,0.1f,0.1f,2.0f,32,32);
		
			// Add ends to cylinder
			glPushMatrix();
				glRotatef(90, 0, 0, 1);
				glRotatef(180, 0, 1, 0);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic2, GL_TRUE);
				// Draw disk/circle
				gluDisk(quadratic2, 0.0f, 0.1f, 32,32);
			glPopMatrix();

			glPushMatrix();
				// Move into position
				glTranslatef(0,0,2);
				glRotatef(90, 0, 0, 1);
				// Bind new texture
				glBindTexture(GL_TEXTURE_2D, textureLog);
				gluQuadricTexture(quadratic3, GL_TRUE);
				// Draw disc/circle
				gluDisk(quadratic3, 0.0f, 0.1f, 32,32);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
}
