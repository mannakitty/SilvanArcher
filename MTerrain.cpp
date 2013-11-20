#include "MTerrain.h"
#include "MTexture.h"
#include "MVertex.h"
#include <vector>

MTerrain::MTerrain()
{}

MTerrain::~MTerrain()
{}

bool MTerrain::Initialise()
{
	// Load the texture
	MTexture texture;
	texture.CreateFromBMP(&m_hTexture, "Resources/Textures/GrassDark.bmp"); 
	
	return true;
}

void MTerrain::Render()
{
	float TERRAIN_SIZE = 500;
	
	GLfloat x, y, z, length, width;
	length = TERRAIN_SIZE / 2.0f;
	width = TERRAIN_SIZE / 2.0f;
	
	// Centre terrain around 0, 0, 0;
	x = -width  / 2;
	y = 0;
	z = -length / 2;

	// Bind the texture	
	glBindTexture(GL_TEXTURE_2D, m_hTexture);

	glNormal3f(0.0f, 1.0f, 0.0f);

	// Draw a quad
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();

}

// This does the same thing as Render() but now it uses a vertex array
void MTerrain::RenderVertexArray()
{
	float TERRAIN_SIZE = 10000;

	GLfloat x, y, z, length, width;
	length = TERRAIN_SIZE / 2.0f;
	width = TERRAIN_SIZE / 2.0f;
	
	//centre texture around 0, 0, 0;
	x = -width  / 2;
	y = 0;
	z = -length / 2;
	
	// Define arrays to hold vertex positions, normals, and texture coords
	GLfloat vertexArray[12];
	GLfloat normalArray[12];
	GLfloat textureCoordArray[8];

	vertexArray[0] = x; vertexArray[1] = y; vertexArray[2] = z; 
	vertexArray[3] = x; vertexArray[4] = y; vertexArray[5] = z + length; 
	vertexArray[6] = x + width; vertexArray[7] = y; vertexArray[8] = z + length; 
	vertexArray[9] = x + width; vertexArray[10] = y; vertexArray[11] = z; 

	normalArray[0] = 0.0f; normalArray[1] = 1.0f; normalArray[2] = 0.0f; 
	normalArray[3] = 0.0f; normalArray[4] = 1.0f; normalArray[5] = 0.0f; 
	normalArray[6] = 0.0f; normalArray[7] = 1.0f; normalArray[8] = 0.0f; 
	normalArray[9] = 0.0f; normalArray[10] = 1.0f; normalArray[11] = 0.0f; 

	textureCoordArray[0] = 1.0f; textureCoordArray[1] = 0.0f;
	textureCoordArray[2] = 1.0f; textureCoordArray[3] = 1.0f;
	textureCoordArray[4] = 0.0f; textureCoordArray[5] = 1.0f;
	textureCoordArray[6] = 0.0f; textureCoordArray[7] = 0.0f;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Give OpenGL pointers to tightly packed arrays
	glNormalPointer(GL_FLOAT, 0, &normalArray[0]);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureCoordArray[0]);
 
	// Bind the texture and draw
	glBindTexture(GL_TEXTURE_2D, m_hTexture);
	glDrawArrays(GL_QUADS, 0, 4);
 
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	
}

// This does the same thing as RenderVertexArray but now uses an MVertex structure
void MTerrain::RenderVertexArrayUsingMVertex()
{
	float TERRAIN_SIZE = 10000;

	GLfloat x, y, z, length, width;
	length = TERRAIN_SIZE / 2.0f;
	width = TERRAIN_SIZE / 2.0f;
	
	//centre texture around 0, 0, 0;
	x = -width  / 2;
	y = 0;
	z = -length / 2;

	// Define the four vertices, each with position, normal, and texture coords
	MVertex v1(x, y, z, 0, 1, 0, 1, 0);
	MVertex v2(x, y, z + length, 0, 1, 0, 1, 1);
	MVertex v3(x + width, y, z + length, 0, 1, 0, 0, 1);
	MVertex v4(x + width, y, z, 0, 1, 0, 0, 0);
	
	// Put vertices into an STL vector
	std::vector <MVertex> vertices;
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
		
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
 
	// Note we now must use the stride parameter (third argument), and indicate the first element with the fourth argument
	glVertexPointer(3, GL_FLOAT, sizeof(MVertex), &vertices[0].x);
	glNormalPointer(GL_FLOAT, sizeof(MVertex), &vertices[0].nx);
	glTexCoordPointer(2, GL_FLOAT, sizeof(MVertex), &vertices[0].s);
 
	// Bind the texture and draw
	glBindTexture(GL_TEXTURE_2D, m_hTexture);
	glDrawArrays(GL_QUADS, 0, 4);
 
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	
}
