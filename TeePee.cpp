#include "TeePee.h"
#include <Windows.h>
#include ".\include\gl.h"

TeePee::TeePee(void)
{
}

TeePee::TeePee(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_vPosition.x = (float)x;
	m_vPosition.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_vPosition);
	m_vPosition.y = y;
	// Set texture 
	MTexture texture;
	texture.CreateFromBMP(&canvasTexture, "Resources/Textures/canvas.bmp");
	// setup boundingbox 
	MVector3f minPoint(2.5f, 0.0f, 2.5f);
	minPoint = m_vPosition - minPoint;
	MVector3f maxPoint(2.5f, 7.0f, 2.5f);
	maxPoint = m_vPosition + maxPoint;
	bBox.Set(minPoint, maxPoint);
	objectMass = 50;
}


TeePee::~TeePee(void)
{
}

void TeePee::Render(void)
{
	// Vector which represents the centre of the object for working out normals 
	MVector3f centre = MVector3f(0.0f, 1.5f, 0.0f);

	glPushMatrix();
		// Move into position and scale tent into wanted size and shape
		glTranslatef(m_vPosition.x , m_vPosition.y, m_vPosition.z);
		glScalef(1.5, 3, 1.5);
		// Sort out texture
		glColor3f(1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, canvasTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Co-ordinates for each point and normals for each worked out by method shown at start of lecture 6
		// by working out the normalised distance between centre of object and point
		GLfloat v0[3] = {0.0f, 3.0f, 0.0f};
		MVector3f working = MVector3f(0.0, 1.5, 0.0);
		working = working - centre;
		working.Normalize();
		GLfloat n0[3] = {working.x, working.y, working.z};
	
		GLfloat v1[3] = {-1.0f, 0.0f, 2.0f};
		working = MVector3f(-1.0f, 0.0f, 2.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n1[3] = {working.x, working.y, working.z};

		GLfloat v2[3] = {1.0f, 0.0f, 2.0f};
		working = MVector3f(1.0f, 0.0f, 2.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n2[3] = {working.x, working.y, working.z};

		GLfloat v3[3] = {2.0f, 0.0f, 1.0f};
		working = MVector3f(2.0f, 0.0f, 1.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n3[3] = {working.x, working.y, working.z};
	
		GLfloat v4[3] = {2.0f, 0.0f, -1.0f};
		working = MVector3f(2.0f, 0.0f, -1.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n4[3] = {working.x, working.y, working.z};
	
		GLfloat v5[3] = {1.0f, 0.0f, -2.0f};
		working = MVector3f(1.0f, 0.0f, -2.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n5[3] = {working.x, working.y, working.z};
	
		GLfloat v6[3] = {-1.0f, 0.0f, -2.0f};
		working = MVector3f(-1.0f, 0.0f, -2.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n6[3] = {working.x, working.y, working.z};
	
		GLfloat v7[3] = {-2.0f, 0.0f, -1.0f};
		working = MVector3f(-2.0f, 0.0f, -1.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n7[3] = {working.x, working.y, working.z};

		GLfloat v8[3] = {-2.0f, 0.0f, 1.0f};
		working = MVector3f(-2.0f, 0.0f, 1.0f);
		working = working - centre;
		working.Normalize();
		GLfloat n8[3] = {working.x, working.y, working.z};

		glBegin(GL_TRIANGLES);
			
			// Drawing each side of the tent asigning texture co-ordinates and normals to each
			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n1);
			glVertex3fv(v1);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n2);
			glVertex3fv(v2);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n2);
			glVertex3fv(v2);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n3);
			glVertex3fv(v3);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n3);
			glVertex3fv(v3);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n4);
			glVertex3fv(v4);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n4);
			glVertex3fv(v4);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n5);
			glVertex3fv(v5);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n5);
			glVertex3fv(v5);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n6);
			glVertex3fv(v6);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n6);
			glVertex3fv(v6);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n7);
			glVertex3fv(v7);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n7);
			glVertex3fv(v7);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n8);
			glVertex3fv(v8);

			glTexCoord2d(0.5, 1);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2d(0.0, 0.0);
			glNormal3fv(n8);
			glVertex3fv(v8);
			glTexCoord2d(1.0, 0.0);
			glNormal3fv(n1);
			glVertex3fv(v1);
		glEnd();
	glPopMatrix();
			
}
