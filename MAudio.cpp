#include "MAudio.h"


MAudio::MAudio()
{}

MAudio::~MAudio()
{}

bool MAudio::Initialise()
{
	// Create an FMOD system
	result = FMOD::System_Create(&m_FmodSystem);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	// Initialise the system
	result = m_FmodSystem->init(32, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	return true;
	
}

// Load an event sound
bool MAudio::LoadEventSound1(char *filename)
{
	result = m_FmodSystem->createSound(filename, FMOD_HARDWARE|FMOD_3D, 0, &m_scream);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	return true;
	

}

// Play an event sound
bool MAudio::PlayEventSound1(MVector3f cameraPosition, MVector3f position)
{
	// Set position and velocity of listener based on the camera
	FMOD_VECTOR pos, vel;
	pos.x =  position.x; 
	pos.y = position.y; 
	pos.z = position.z;
	vel.x = 1; 
	vel.y = 1; 
	vel.z = 1; 
	
	result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, m_scream, false, &m_soundEffectChannel1);
	FmodErrorCheck(result);
	m_soundEffectChannel1->setVolume(1);
	m_soundEffectChannel1->set3DMinMaxDistance(2.5, 100);
	m_soundEffectChannel1->set3DAttributes(&pos, &vel);
	if (result != FMOD_OK)
		return false;

	return true;
}

// Load an event sound
bool MAudio::LoadEventSound2(char *filename)
{
	result = m_FmodSystem->createSound(filename, FMOD_HARDWARE|FMOD_3D, 0, &m_explosion);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	return true;
	

}

// Play an event sound
bool MAudio::PlayEventSound2(MVector3f cameraPosition, MVector3f position)
{
	// Set position and velocity of listener based on the camera
	FMOD_VECTOR pos, vel;
	pos.x =  position.x; 
	pos.y = position.y; 
	pos.z = position.z;
	vel.x = 0; 
	vel.y = 0; 
	vel.z = 0; 
	
	result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, m_explosion, false, &m_soundEffectChannel2);
	FmodErrorCheck(result);
	m_soundEffectChannel2->setVolume(1);
	m_soundEffectChannel2->set3DMinMaxDistance(2.5, 100);
	m_soundEffectChannel2->set3DAttributes(&pos, &vel);
	if (result != FMOD_OK)
		return false;

	return true;
}

// Load an event sound
bool MAudio::LoadEventSound3(char *filename)
{
	result = m_FmodSystem->createSound(filename, FMOD_HARDWARE|FMOD_3D, 0, &m_ting);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	return true;
	

}

// Play an event sound
bool MAudio::PlayEventSound3(MVector3f cameraPosition, MVector3f position)
{
	// Set position and velocity of listener based on the camera
	FMOD_VECTOR pos, vel;
	pos.x =  position.x; 
	pos.y = position.y; 
	pos.z = position.z;
	vel.x = 0; 
	vel.y = 0; 
	vel.z = 0; 
	
	result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, m_ting, false, &m_soundEffectChannel3);
	FmodErrorCheck(result);
	m_soundEffectChannel3->setVolume(1);
	m_soundEffectChannel3->set3DMinMaxDistance(2.5, 100);
	m_soundEffectChannel3->set3DAttributes(&pos, &vel);
	if (result != FMOD_OK)
		return false;

	return true;
}


// Load music stream
bool MAudio::LoadMusicStream(char *filename)
{
	result = m_FmodSystem->createStream(filename, FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &m_music);
	FmodErrorCheck(result);

	if (result != FMOD_OK) 
		return false;

	return true;
	

}

// Play a music stream
bool MAudio::PlayMusicStream()
{
	result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
	FmodErrorCheck(result);

	if (result != FMOD_OK)
		return false;
	m_musicChannel->setVolume(0.5);
	return true;
}

// Check for error
void MAudio::FmodErrorCheck(FMOD_RESULT result)
{						
	if (result != FMOD_OK) {
		const char *errorString = FMOD_ErrorString(result);
		 MessageBox(NULL, errorString, "FMOD Error", MB_OK);
		// Warning: error message commented out -- if headphones not plugged into computer in A220, error occurs
	}
}

void MAudio::UpdateEventSound(MCamera camera)
{
	
	//vectors to update listener position
	FMOD_VECTOR listenerPosition, listenerVelocity, upVector, viewVector;

	MVector3f cameraPosition = camera.GetPosition();
	MVector3f dir = camera.View() - camera.GetPosition();  // note: viewVector pointing backwards due to right-handed coordinate system
	dir.Normalize();
	MVector3f up = camera.UpVector();

	listenerPosition.x = cameraPosition.x;
	listenerPosition.y = cameraPosition.y;
	listenerPosition.z = cameraPosition.z;
	listenerVelocity.x = 0;
	listenerVelocity.y = 0;
	listenerVelocity.z = 0;
	upVector.x = up.x;
	upVector.y = up.y;
	upVector.z = up.z;
	viewVector.x = dir.x;
	viewVector.y = dir.y;
	viewVector.z = dir.z;

	// Update the listener position, velocity, and orientation based on the camera
	m_FmodSystem->set3DListenerAttributes(0, &listenerPosition, &listenerVelocity, &viewVector, &upVector);
	m_FmodSystem->update();

}

