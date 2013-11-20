#include "IntroScreen.h"
#include <stdio.h>										// Header File For The Standard Input/Output Functions
#include "MTexture.h"
#include ".\include\glut.h"


IntroScreen::IntroScreen(void)
{
	
}


IntroScreen::~IntroScreen(void)
{
}

void IntroScreen::Render(RECT  g_rRect)
{
	    // Set hight and width as the current height and width of the window
        int w = g_rRect.right;
        int h = g_rRect.bottom;

		glColor3f(0, 0, 0);
        // Draw text
        sprintf_s(Instructions, "Up Arrow/W - Move Forward");
        text.Render(Instructions, 50, 300,  GLUT_BITMAP_HELVETICA_18 );
        sprintf_s(Instructions, "Down Arrow/S - Move Backwards");
        text.Render(Instructions, w - 850, 300,  GLUT_BITMAP_HELVETICA_18 );
        sprintf_s(Instructions, "Right Arrow/D - Strafe Right");
        text.Render(Instructions, 50, 330,  GLUT_BITMAP_HELVETICA_18 );
        sprintf_s(Instructions, "Left Arrow/A - Strafe Left");
        text.Render(Instructions, w - 850, 330,  GLUT_BITMAP_HELVETICA_18 );
        sprintf_s(Instructions, "Mouse - Camera Control");
        text.Render(Instructions, 50, 360,  GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "1 - Fire Arrows");
		text.Render(Instructions, w - 850, 360, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Ingame Items:");
		text.Render(Instructions, 350, 400, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Fire Arrows:");
		text.Render(Instructions, (w/2) - 365, 440, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Turn normal arrows");
		text.Render(Instructions, (w/2) - 379, 470, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "into fire arrows for 20s");
		text.Render(Instructions, (w/2) - 385, 500, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Hearts:");
		text.Render(Instructions, 85, 440, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Increase player health");
		text.Render(Instructions, 50, 470, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Barrels:");
		text.Render(Instructions, w - 800, 440, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Can be exploded");
		text.Render(Instructions, w - 825, 470, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "with fire arrows");
		text.Render(Instructions, w - 820, 500, GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(Instructions, "Press 1 for easy mode, Press 2 for hard mode");
		text.Render(Instructions, 280, 590, GLUT_BITMAP_HELVETICA_18 );

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
      
        glBindTexture(GL_TEXTURE_2D, background);

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



void IntroScreen::init()
{
	//Set background image as texture 
	MTexture texture;
	texture.CreateFromBMP(&background, "Resources/Textures/TitleScreen.bmp");
}
