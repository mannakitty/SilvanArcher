#include "EndScreen.h"
#include <stdio.h>										// Header File For The Standard Input/Output Functions
#include "MTexture.h"
#include ".\include\glut.h"

EndScreen::EndScreen(void)
{
}


EndScreen::~EndScreen(void)
{
}

void EndScreen::Render(RECT  g_rRect)
{
	    // Set hight and width as the current height and width of the window
        int w = g_rRect.right;
        int h = g_rRect.bottom;

		// Change the progection mode to orthographic using hight and width
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glLoadIdentity();
        glDisable(GL_LIGHTING);
       
        // Set background as texture to render
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
      
        glBindTexture(GL_TEXTURE_2D, background2);

        glColor3f(1, 1, 1);

        // Draw textured quad with background image
        glBegin(GL_QUADS);
		        glTexCoord2f(0.0f, 0.0f);
                glVertex3f(0, 0, 0);
				glTexCoord2f(1.0f, 0.0f);
                glVertex3f(w, 0, 0);
				glTexCoord2f(1.0f, 1.0f);
                glVertex3f(w, h, 0);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(0, h, 0);
		glEnd();

         // Change projection mode back
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
       
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

		glDisable(GL_TEXTURE);
		glDisable(GL_TEXTURE_2D);

		
}



void EndScreen::init()
{
	//Set background image as texture 
	MTexture texture;
	texture.CreateFromBMP(&background2, "Resources/Textures/EndScreen.bmp");
}

