#include "MText.h"

MText::MText()
{}

MText::~MText()
{}



void MText::SetOrthographicProjection()
{
	int w = 400;
	int h = 400;
	// switch to pwrojection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, 800, 0, 600);
	// invert the y axis, down is positive
	glScalef(1.0f, -1.0f, 1.0f);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -600, 0);
	glMatrixMode(GL_MODELVIEW);
}


void MText::ResetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}



void MText::RenderBitmapString(float x, float y, void *font,char *string)
{
  char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void MText::Render(char text[20], float x, float y, void *font)
{
    glPushMatrix();
	SetOrthographicProjection();
	glLoadIdentity();
	RenderBitmapString(x, y, font, text);
	ResetPerspectiveProjection();
	glPopMatrix();
}