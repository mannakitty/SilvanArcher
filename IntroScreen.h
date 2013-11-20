#pragma once

#include "MText.h"
#include "MTexture.h"
#include "MVector3f.h"

// Class to represent the intro screen.  Holds all items which will need to be rendered to screen whilst in this state.

class IntroScreen
{
private:
	char Instructions[70];								// Character array to store text for the instructions
	MText text;											// Text
	GLuint background;									// Background
	

public:
	// Constructors
	IntroScreen(void);
	// Deconstructor
	~IntroScreen(void);
	// Render method
	void init();
	void Render(RECT  g_rRect);
};

