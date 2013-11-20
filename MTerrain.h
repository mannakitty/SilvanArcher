#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library


class MTerrain
{
public:
	MTerrain();
	~MTerrain();
	bool Initialise();
	void Render();
	void RenderVertexArray();
	void RenderVertexArrayUsingMVertex();
	
private:
	UINT m_hTexture;
	
};