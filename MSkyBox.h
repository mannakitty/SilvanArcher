#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"								// Header File For The OpenGL32 Library


typedef enum {
	SKYBOX_BACK_ID,
	SKYBOX_FRONT_ID,
	SKYBOX_BOTTOM_ID,
	SKYBOX_TOP_ID,
	SKYBOX_LEFT_ID,
	SKYBOX_RIGHT_ID
} BoxSideTypes;

class MSkyBox
{
public:
	MSkyBox();
	~MSkyBox();
	bool Create(const char *bmpDirectory, const float fSize);
	void Render(float x, float y, float z, float width, float height, float length);

private:
	
	// std::vector<MTexture> m_textureHandles;
	unsigned int m_textureIds[6];

};