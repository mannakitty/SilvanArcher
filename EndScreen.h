#pragma once
#include "MTexture.h"

// Class to represent the end screen shown at the end of the game

class EndScreen
{
public:
	// constructor
	EndScreen(void);
	// deconstructor
	~EndScreen(void);
	// initialise method
	void init();
	// render end screen
	void Render(RECT  g_rRect);
private:
	GLuint background2;									// Background
};

