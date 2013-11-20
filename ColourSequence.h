#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library
#include "MVector3f.h"
#include <vector>

// Class used to represent colour sequences used to particle emitter

class ColourSequence
{
public:
	// constructor
	ColourSequence();
	// deconstructor
	~ColourSequence();
	// methods to go from black to white or visa versa
	void WhiteToBlack(int N);
	void WhiteToBlackFast(int N);
	void BlackToWhite(int N);
	void BlackToWhiteFast(int N);
	// methods to go from yellow to red or visa versa
	void YellowToRedFast(int N);
	void RedToYellowFast(int N);

	// holds wanted colour sequence
	std::vector<MVector3f> m_colourSequence;

};

