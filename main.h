#ifndef _MAIN_H
#define _MAIN_H


#include <windows.h>									// Header File For The Windows Library
#include <stdio.h>										// Header File For The Standard Input/Output Functions
#include <stdlib.h>										// Header File For The Standard Library
#include <math.h>										// Header File For The Math header file
#include ".\include\glew.h"									// Header File For The Glaux Library
#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glu.h"									// Header File For The GLu32 Library
#include ".\include\glaux.h"									// Header File For The Glaux Library

#include "MVector3f.h"


//#define SCREEN_WIDTH 1440								// Define a screen width of 800 pixels
//#define SCREEN_HEIGHT 900								// Define a screen height of 600 pixels
#define SCREEN_DEPTH 16									// Define 16 bit pixel depth


#define GL_CLAMP_TO_EDGE	0x812F						

 

extern bool  g_bFullScreen;									// Set full screen as default
extern HWND  g_hWnd;										// This is the handle for the window
extern RECT  g_rRect;										// This holds the window dimensions
extern HDC   g_hDC;											// General HDC - (handle to device context)
extern HGLRC g_hRC;											// General OpenGL_DC - Our Rendering Context for OpenGL
extern HINSTANCE g_hInstance;								// This holds our window hInstance

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;


// This is our MAIN() for windows
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow);

// The window proc which handles all of window's messages.
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// This controls our main program loop
WPARAM MainLoop();

// This changes the screen to full screen mode
void ChangeToFullScreen();

// This is our own function that makes creating a window modular and easy
HWND CreateMyWindow(LPSTR strWindowName, int width, int height, DWORD dwStyle, bool bFullScreen, HINSTANCE hInstance);

// This allows us to configure our window for OpenGL and backbuffered
bool bSetupPixelFormat(HDC hdc);

// This inits our screen translations and projections
void SizeOpenGLScreen(int width, int height);

// This sets up OpenGL
void InitializeOpenGL(int width, int height);

// This initializes the whole program
void Init(HWND hWnd);

// This draws everything to the screen
void RenderScene();

//Method to detect camera movement (moved from camera class)
void CameraKeys();

//Method to make avatar come down after moving over hilly terrain
void AvatarGravity();

//Method to detect collision with the terrain
void TerrainCollisionDetect(MVector3f& vPos, MVector3f& vNewPos, MVector3f& vView);

void CollisionDetection();


// This frees all our memory in our program
void DeInit();

#endif 
