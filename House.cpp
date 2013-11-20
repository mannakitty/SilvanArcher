#include "House.h"
#include ".\include\glut.h"	

House::House(void)
{
}

House::House(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Store x and z positions
	m_vPosition.x = x;
	m_vPosition.z = z;
	// Find high of terrain at coordinate and store
	float y = g_heightMapTerrain.ReturnGroundHeight(m_vPosition);
	m_vPosition.y = y;
	// Store textures
	MTexture texture;
	texture.CreateFromBMP(&textureBuilding, "Resources/Textures/Wood Panel.bmp");
	texture.CreateFromBMP(&textureRoof, "Resources/Textures/thatch.bmp");
	objectMass = 100;
}


House::~House(void)
{
}

void House::Render(void)
{
	// Enable and add texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureBuilding);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glPushMatrix();
		// Vector which represents the centre of the object for working out normals 
		MVector3f centreSquare = MVector3f(0.0f, 0.0f, 0.0f);
		MVector3f centerTriangle = MVector3f(0.0f, -2.25f, 0.0f);

		// Points of square and normals for these points worked out by method given at the start of lecture 6
		GLfloat v0[3] = {7.5f, 7.5f,-7.5f};
		MVector3f working = MVector3f(7.5f, 7.5f,-7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n0[3] = {working.x, working.y, working.z};

		GLfloat v1[3] = {-7.5f, 7.5f,-7.5f};
		working = MVector3f(-7.5f, 7.5f,-7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n1[3] = {working.x, working.y, working.z};

		GLfloat v2[3] = {-7.5f, 7.5f, 7.5f};
		working = MVector3f(-7.5f, 7.5f, 7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n2[3] = {working.x, working.y, working.z};

		GLfloat v3[3] = {7.5f, 7.5f, 7.5f};
		working = MVector3f(7.5f, 7.5f, 7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n3[3] = {working.x, working.y, working.z};

		GLfloat v4[3] = {7.5f,-7.5f, 7.5f};
		working = MVector3f(7.5f,-7.5f, 7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n4[3] = {working.x, working.y, working.z};

		GLfloat v5[3] = {-7.5f,-7.5f, 7.5f};
		working = MVector3f(-7.5f,-7.5f, 7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n5[3] = {working.x, working.y, working.z};

		GLfloat v6[3] = {-7.5f,-7.5f,-7.5f};
		working = MVector3f(-7.5f,-7.5f,-7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n6[3] = {working.x, working.y, working.z};

		GLfloat v7[3] = {7.5f,-7.5f,-7.5f};
		working = MVector3f(7.5f,-7.5f,-7.5f);
		working = working - centreSquare;
		working.Normalize();
		GLfloat n7[3] = {working.x, working.y, working.z};
		
		// Move and rotate into position
		glTranslatef(m_vPosition.x , m_vPosition.y + 3.5, m_vPosition.z);
		glRotatef(45, 0, 1, 0);
		glScalef(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
			glColor3f(1.0f,1.0f,1.0f); 
			
			// Top Face
			glTexCoord2f(1.0f, 1.0f);
			glNormal3fv(n0);
			glVertex3fv(v0);
			glTexCoord2f(1.0f, 0.0f);
			glNormal3fv(n1);
			glVertex3fv(v1);
			glTexCoord2f(0.0f, 0.0f);
			glNormal3fv(n2);
			glVertex3fv(v2);
			glTexCoord2f(0.0f, 1.0f);
			glNormal3fv(n3);
			glVertex3fv(v3);          
		
			// Bottom Face
			glTexCoord2f(1.0f, 1.0f);
			glNormal3fv(n4);
			glVertex3fv(v4);          
			glTexCoord2f(1.0f, 0.0f);
			glNormal3fv(n5);
			glVertex3fv(v5);          
			glTexCoord2f(0.0f, 0.0f);
			glNormal3fv(n6);
			glVertex3fv(v6);          
			glTexCoord2f(0.0f, 1.0f);
			glNormal3fv(n7);
			glVertex3fv(v7);          
			
			// Front face
			glTexCoord2f(1.0f, 1.0f);
			glNormal3fv(n3);
			glVertex3fv(v3);          
			glTexCoord2f(1.0f, 0.0f);
			glNormal3fv(n2);
			glVertex3fv(v2);          
			glTexCoord2f(0.0f, 0.0f);
			glNormal3fv(n5);
			glVertex3fv(v5);          
			glTexCoord2f(0.0f, 1.0f);
			glNormal3fv(n4);
			glVertex3fv(v4);          
			
			// Back face
			glTexCoord2f(1.0f, 1.0f);
			glNormal3fv(n7);
			glVertex3fv(v7);          
			glTexCoord2f(1.0f, 0.0f);
			glNormal3fv(n6);
			glVertex3fv(v6);          
			glTexCoord2f(0.0f, 0.0f);
			glNormal3fv(n1);
			glVertex3fv(v1);          
			glTexCoord2f(0.0f, 1.0f);
			glNormal3fv(n0);
			glVertex3fv(v0);          
			
			// Left face
			glTexCoord2f(1.0f, 1.0f);
			glNormal3fv(n2);
			glVertex3fv(v2);          
			glTexCoord2f(1.0f, 0.0f);
			glNormal3fv(n1);
			glVertex3fv(v1);          
			glTexCoord2f(0.0f, 0.0f);
			glNormal3fv(n6);
			glVertex3fv(v6);          
			glTexCoord2f(0.0f, 1.0f);
			glNormal3fv(n5);
			glVertex3fv(v5);          
			
			// Right face
			glTexCoord2f(1.0f, 1.0f);
			glNormal3fv(n0);
			glVertex3fv(v0);          
			glTexCoord2f(1.0f, 0.0f);
			glNormal3fv(n3);
			glVertex3fv(v3);          
			glTexCoord2f(0.0f, 0.0f);
			glNormal3fv(n4);
			glVertex3fv(v4);          
			glTexCoord2f(0.0f, 1.0f);
			glNormal3fv(n7);
			glVertex3fv(v7);          
		glEnd();    
		// Bind texture of roof
		glBindTexture(GL_TEXTURE_2D, textureRoof);
		glPushMatrix();

			// Points of square and normals for these points worked out by method given at the start of lecture 6
			GLfloat v8[3] = {0.0f, 3.0f, 0.0f};
			working = MVector3f(0.0f, 3.0f, 0.0f);
			working = working - centerTriangle;
			working.Normalize();
			GLfloat n8[3] = {working.x, working.y, working.z};

			GLfloat v9[3] = {-7.5f,-7.5f, 7.5f};
			working = MVector3f(-7.5f,-7.5f, 7.5f);
			working = working - centerTriangle;
			working.Normalize();
			GLfloat n9[3] = {working.x, working.y, working.z};

			GLfloat v10[3] = {7.5f,-7.5f, 7.5f};
			working = MVector3f(7.5f,-7.5f, 7.5f);
			working = working - centerTriangle;
			working.Normalize();
			GLfloat n10[3] = {working.x, working.y, working.z};

			GLfloat v11[3] = {7.5f,-7.5f, -7.5f};
			working = MVector3f(7.5f,-7.5f, -7.5f);
			working = working - centerTriangle;
			working.Normalize();
			GLfloat n11[3] = {working.x, working.y, working.z};

			GLfloat v12[3] = {-7.5f,-7.5f, -7.5f};
			working = MVector3f(-7.5f,-7.5f, -7.5f);
			working = working - centerTriangle;
			working.Normalize();
			GLfloat n12[3] = {working.x, working.y, working.z};

			// Move into position
			glTranslatef(0, 15, 0);
			glBegin(GL_TRIANGLES);

				glColor3f(1.0f,1.0f,1.0f); 

				// Front face
				glTexCoord2f(0.5f, 1.0f);
				glNormal3fv(n8);
				glVertex3fv(v8);          
				glTexCoord2f(0.0f, 0.0f);
				glNormal3fv(n9);
				glVertex3fv(v9);          
				glTexCoord2f(1.0f, 0.0);
				glNormal3fv(n10);
				glVertex3fv(v10);          
				
				// Right face
				glTexCoord2f(0.5f, 1.0f);
				glNormal3fv(n8);
				glVertex3fv(v8);          
				glTexCoord2f(0.0f, 0.0f);
				glNormal3fv(n10);
				glVertex3fv(v10);          
				glTexCoord2f(1.0f, 0.0);
				glNormal3fv(n11);
				glVertex3fv(v11);         
				
				// Back face
				glTexCoord2f(0.5f, 1.0f);
				glNormal3fv(n8);
				glVertex3fv(v8);          
				glTexCoord2f(0.0f, 0.0f);
				glNormal3fv(n11);
				glVertex3fv(v11);         
				glTexCoord2f(1.0f, 0.0);
				glNormal3fv(n12);
				glVertex3fv(v12);         
				
				// Left face
				glTexCoord2f(0.5f, 1.0f);
				glNormal3fv(n8);
				glVertex3fv(v8);          
				glTexCoord2f(0.0f, 0.0f);
				glNormal3fv(n12);
				glVertex3fv(v12);          
				glTexCoord2f(1.0f, 0.0);
				glNormal3fv(n9);
				glVertex3fv(v9);          

			glEnd();			
		glPopMatrix();
	glPopMatrix();
}
