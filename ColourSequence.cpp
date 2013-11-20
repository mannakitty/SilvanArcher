#include "ColourSequence.h"


ColourSequence::ColourSequence(void)
{
}


ColourSequence::~ColourSequence(void)
{
}

void ColourSequence::WhiteToBlack(int N)
{
	for (int i = 0; i <= N; i++) {
		float f = 1 - (float) i / (float) N;
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);
	}

}


void ColourSequence::WhiteToBlackFast(int N)
{
	int Nover2 = N / 2;
	for (int i = 0; i <= Nover2; i++) {
		float f = 1 - (float) i / (float) Nover2;
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);
	}

	for (int i = Nover2+1; i < N; i++) {
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);

	}

}


void ColourSequence::BlackToWhiteFast(int N)
{
	int Nover2 = N / 50;
	for (int i = 0; i <= Nover2; i++) {
		float f = (float) i / (float) Nover2;
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);
	}

	for (int i = Nover2+1; i < N; i++) {
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);

	}
}

void ColourSequence::BlackToWhite(int N)
{
	for (int i = 0; i <= N; i++) {
		float f = (float) i / (float) N;
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);
	}

}

void ColourSequence::YellowToRedFast(int N)
{	
	//cirlce through a series of colors between yellow and red
	int Nover2 = N / 50;
	for (int i = 0; i <= Nover2; i++) {
		float f = (float) i / (float) Nover2;
		MVector3f colour = MVector3f(1.0f, f, 0.0f);
		m_colourSequence.push_back(colour);
	}

	for (int i = Nover2+1; i < N; i++) {
		MVector3f colour = MVector3f(1, 1, 0);
		m_colourSequence.push_back(colour);

	}
}

void ColourSequence::RedToYellowFast(int N)
{
	//cirlce through a series of colors between yellow and red quickly 
	int Nover2 = N / 50;
	for (int i = 0; i <= Nover2; i++) {
		float f = (((float) i / (float) Nover2)) + 0.5;
		MVector3f colour = MVector3f(1.0f, f, 0.0f);
		m_colourSequence.push_back(colour);
	}

	for (int i = Nover2+1; i < N; i++) {
		MVector3f colour = MVector3f(1.0f, 0.8f, 0.0f);
		m_colourSequence.push_back(colour);

	}
}