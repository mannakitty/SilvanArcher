#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\fmod.hpp"
#include ".\include\fmod_errors.h"									// Header File For The Glaux Library
#include "MVector3f.h"
#include "MCamera.h"


class MAudio
{
public:
	MAudio();
	~MAudio();
	bool Initialise();
	bool LoadEventSound1(char *filename);
	bool PlayEventSound1(MVector3f cameraPosition, MVector3f position);
	bool LoadEventSound2(char *filename);
	bool PlayEventSound2(MVector3f cameraPosition, MVector3f position);
	bool LoadEventSound3(char *filename);
	bool PlayEventSound3(MVector3f cameraPosition, MVector3f position);
	bool LoadMusicStream(char *filename);
	bool PlayMusicStream();
	void UpdateEventSound(MCamera camera);

private:
		

	void FmodErrorCheck(FMOD_RESULT result);


	FMOD_RESULT result;
	FMOD::System* m_FmodSystem;	// the global variable for talking to FMOD
	FMOD::Sound *m_scream;
	FMOD::Sound *m_explosion;
	FMOD::Sound *m_ting;
	FMOD::Channel* m_soundEffectChannel1;
	FMOD::Channel* m_soundEffectChannel2;
	FMOD::Channel* m_soundEffectChannel3;
	
	FMOD::Sound *m_music;
	FMOD::Channel* m_musicChannel;

};
