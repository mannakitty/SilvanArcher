#include "SpriteExplosion.h"

SpriteExplosion::SpriteExplosion(MVector3f p)
{

	m_active = false;
	position = p;
}

SpriteExplosion::~SpriteExplosion()
{}


void SpriteExplosion::Activate()
{
	m_active = true;
	m_frame = 0;
	m_elapsedTime = 0;
}


void SpriteExplosion::Update(float dt)
{

	if (m_active == false)
		return;

	float frameTime = 1.0f / 30.0f;  // 30 frames per second

	m_elapsedTime += dt;

	if (m_elapsedTime > frameTime) {
		m_frame++;
		if (m_frame >= m_totalFrames) {
			m_frame = 0;
			m_active = false;
		}
		m_elapsedTime -= frameTime;
	}
}


bool SpriteExplosion::Initialise(const char *filename, const int numFramesX, const int numFramesY, const int totalFrames)
{

	// Load the texture
	tex.Load((char *)filename); // Loads an image.  Make sure the image is in a 32 bit format (tga) with transparency
	
	m_framesX = numFramesX;
	m_framesY = numFramesY;

	m_frameWidth = tex.width / m_framesX;
	m_frameHeight = tex.height / m_framesY;

	m_frame = 0;
	m_totalFrames = totalFrames;

	m_active = false;

	return true;
}




void SpriteExplosion::Render(MVector3f lookAt, MVector3f upVector, float width, float height)
{

	if (m_active == false)
		return;



	float fImageWidth = (float) tex.width;
	float fImageHeight = (float) tex.height;

	int xIndex = m_frame % m_framesX;
	int yIndex = (m_framesY - 1) - m_frame / m_framesX;


	// Form a quad at p in the plane orthogonal to the lookAt vector
	MVector3f xAxis = lookAt % upVector;
	xAxis.Normalize();
	MVector3f yAxis = upVector;
	yAxis.Normalize();

	// Determine the coordinates of the billboarded quad
	MVector3f p1 = position - width*xAxis - height*yAxis;
	MVector3f p2 = position + width*xAxis - height*yAxis;
	MVector3f p3 = position + width*xAxis + height*yAxis;
	MVector3f p4 = position - width*xAxis + height*yAxis;

	// Bind the texture	
	tex.Use();				// Binds the bitmap for use

	glColor3f(1, 1, 1);

	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform



	// Draw a textured quad with the current frame
	// Be sure to get the texture coordinates that match the current frame
	glBegin(GL_QUADS);		
		glTexCoord2f(xIndex*(m_frameWidth/fImageWidth), yIndex*(m_frameHeight/fImageHeight)); 
		glVertex3f(p1.x, p1.y, p1.z);
		glTexCoord2f((xIndex+1)*(m_frameWidth/fImageWidth), yIndex*(m_frameHeight/fImageHeight)); 
		glVertex3f(p2.x, p2.y, p2.z);
		glTexCoord2f((xIndex+1)*(m_frameWidth/fImageWidth), (yIndex+1)*(m_frameHeight/fImageHeight)); 
		glVertex3f(p3.x, p3.y, p3.z);
		glTexCoord2f(xIndex*(m_frameWidth/fImageWidth), (yIndex+1)*(m_frameHeight/fImageHeight)); 
		glVertex3f(p4.x, p4.y, p4.z);
	glEnd();

	glDisable(GL_BLEND);


}