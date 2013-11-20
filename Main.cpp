/* Advanced Games Technology IN3026 Template
 * Using materials taught by Dr Greg Slabaugh, Dr Chris Child, Dr Dean Mohamedally, 
 * Ben Humphrey (gametutorials.com), Matthew Fairfax and others.
 * For educational use by School of Informatics, City University London UK.
 * 
 * This template consists of an object orientated 3DS model loader, skybox, 
 * terrain, camera methods, lighting methods, audio, simply physics, 
 * texturing in BMP/TGA formats and text rendering to screen. 
 *
 * Modification potentials (template has initial methods for): change terrain types, 
 * load in new models, set up new lights, add in additional music/soundFX, modify camera controls, 
 * put in a startup screen, put in better terrain and collision detection, more advanced physics.
 *
 * Template version 1.5a 03/10/2012
 * 
 */

#pragma comment(lib, "winmm.lib")						// Added for timeGetTime()
 
#include <windows.h>
#include <winuser.h>

#include "main.h"	
#include "MTerrain.h"
#include "MCamera.h"										
#include "MLightingEffects.h"
#include "MSecondaryObjects.h"
#include "MSkybox.h"
#include "MTimer.h"
#include "MText.h"
#include "MHighResolutionTimer.h"
#include "MBouncingBall.h"
#include "MAudio.h"
#include "MHeightMapTerrain.h"
#include "BasicItem.h"
#include "BasicMesh.h"
#include "IntroScreen.h"
#include "Log.h"
#include "House.h"
#include "Barrel.h"
#include "TeePee.h"
#include "MaterialEffects.h"
#include "CampFire.h"
#include "MCrossFade.h"
#include "Pillar.h"
#include "Tree.h"
#include "BigSpider.h"
#include "KillerAnt.h"
#include "Heart.h"
#include "DeadTree.h"
#include "Arrow.h"
#include "FireArrow.h"
#include "MCollisionDetection.h"
#include "FireParticleEmitter.h"
#include "SpriteExplosion.h"
#include "EndScreen.h"
#include ".\include\glut.h"	

bool  g_bFullScreen = FALSE;							// Set full screen as default
HWND  g_hWnd;											// This is the handle for the window
RECT  g_rRect;											// This holds the window dimensions
HDC   g_hDC;											// General HDC - (handle to device context)
HGLRC g_hRC;											// General OpenGL_DC - Our Rendering Context for OpenGL
HINSTANCE g_hInstance;									// This holds the global hInstance for UnregisterClass() in DeInit()
UINT TimerID;											// Name of the win32 timer
const UINT_PTR AvatarTimer = 101;						// The Win32 timer id
MHighResolutionTimer g_GameLoopTimer;					// Timer for the game loop
double dt = 0.0f;
MBouncingBall g_ball;
bool introScreen = true;								// To check whether we are on the introscreen
IntroScreen m_IntroScreen;								// Object to control rendering for introscreen
bool fire = false;										// To check whether fire arrow been picked up
bool backwards = false;									// For collision detection so you do not move backwards through them
bool endScreen = false;									// Check if end screen should be showed or not
EndScreen m_endscreen;									// Class to represent end screen
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

typedef enum {
	TERRAIN_PLANAR,
	TERRAIN_HEIGHTMAP,
} g_terrainTypes;
int g_terrainType = TERRAIN_HEIGHTMAP;
bool g_wireframe = false;

MCamera camera;										// This is our global camera object
MTerrain terrain;									// The terrain in the scene
MSkyBox skyBox;										// A box surrounding the camera to model the background
MText text;											// Text
MLightingEffects lightingEffects;					// The scene lighting
MaterialEffects materialEffects;					// Materials
MTimer timer(0, 0);									// Timer for how long is left in the game
MHighResolutionTimer timeBetweenAttacks;			// time between enemy attacks 
MHighResolutionTimer timeBetweenEffects;			// time before player can take damage between two attacks
MHighResolutionTimer fireTimer;						// time before player can take damage between two attacks
MHighResolutionTimer jitterTime;					// Time the jitter effect should be active
MHighResolutionTimer ArrowAttacks;					// time between arrow attacks
char TimerText[26];									// Character array to store the text for the timer
char ScoreText[26];									// Chatacter array to store text for the score
char HealthText[26];								// Character array to store text for health
char FireText[26];									// Character array to store text for whether fire arrows picked up or not
int score;											// Int to represent the score
int health;											// Int to represent health - die when 0
MAudio g_audio;
MHeightMapTerrain g_heightMapTerrain;				// Hight map
MCrossFade crossFadeRed;							// To enable cross fade effect when attacked
MCrossFade crossFadeWhite;							// Cross fade for when barrels explode
vector<BasicItem*> basicItems;						// Container to contain all basic items
vector<BasicMesh*> basicMeshs;						// Container to contain all mesh objects
vector<Arrow*> arrows;								// Container to hold all arrows
vector<BasicMesh*> enemies;							// Container to hold enemies
vector<Barrel*> barrels;							// Container to hold barrels
vector<BasicMesh*> powerUps;						// Container to hold powerups
vector<SpriteExplosion*> explosions;				// Container to hold explosions
vector<BigSpider*> boss;							// Container to hold boss
bool mMove;											// can camera move
FireParticleEmitter fireParticleE;					// Particle emitter for fire
bool jitter = false;								// boolean to represent if camera jitter effect active
float playerMass;									// Mass the player has when colliding with objects 

void UpdateFrameRate(float dt)
{
	static int framesPerSecond = 0;
	static float elapsedTime = 0.0f;

	// Increase the elapsed time and frame counter
	elapsedTime += dt;
    framesPerSecond++;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
    if(elapsedTime > 1.0f )
    {
		elapsedTime = 0.0f;
		
		//// Copy the frames per second into a string to display in the window title bar
		char strFrameRate[50] = {0};			// We will store the string here for the window title
		sprintf_s(strFrameRate, "Current Frames Per Second: %d", int(framesPerSecond));

		//// Set the window title bar to our string
		SetWindowText(g_hWnd, strFrameRate);

		// Reset the frames per second
        framesPerSecond = 0;
    }
}
		

void Init(HWND hWnd)
{
	g_hWnd = hWnd;										// Assign the window handle to a global window handle
	GetClientRect(g_hWnd, &g_rRect);					// Assign the windows rectangle to a global RECT
	InitializeOpenGL(g_rRect.right, g_rRect.bottom);	// Init OpenGL with the global rect

	// Call glewInit to initialise GLEW.  
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(1);
    }

	glEnable(GL_DEPTH_TEST);							// Enables depth testing
	glEnable(GL_TEXTURE_2D);							// Enable texture mapping
	glEnable(GL_CULL_FACE);								// Turn on back face culling
	
	// Initialise the skybox, secondary objects and terrain
	skyBox.Create("", 0.0f);
	terrain.Initialise();

	// Give our camera a starting point in the world
	camera.PositionCamera( 45, 3, 45,	0, 0, 1,	0, 1, 0);

	g_audio.Initialise();
	g_audio.LoadEventSound1("./Resources/Audio/scream2.wav");				// Royalty free sound from freesound.org
	g_audio.LoadEventSound2("./Resources/Audio/explosion.wav");
	g_audio.LoadEventSound3("./Resources/Audio/ting 6.wav");
	g_audio.LoadMusicStream("./Resources/Audio/Birdsong.mp3");	// Royalty free from freesound.org

	
	// Drop a ball from 30 meters up
	g_ball.Initialise(MVector3f(60.0f, 30.0f, 60.0f), MVector3f(0.0f, 0.0f, 0.0f), MVector3f(0.0f, -9.8f, 0.0f), 0.9f, 0.25f);


	if (g_terrainType == TERRAIN_PLANAR) {
		terrain.Initialise();
	} else if (g_terrainType == TERRAIN_HEIGHTMAP) {
		g_heightMapTerrain.GenerateFromBMP("./Resources/Terrain/terrainHeightMap.bmp", MVector3f(0, 0, 0), 250, 250, 7.5);

	}

	// Create basic objects
	basicItems.push_back(new House(-80, -100, g_heightMapTerrain));
	basicItems.push_back(new House(-60, 77, g_heightMapTerrain));
	basicItems.push_back(new TeePee(30, 60, g_heightMapTerrain));
	basicItems.push_back(new Log(40, 70, g_heightMapTerrain));
	basicItems.push_back(new Log(56, -23, g_heightMapTerrain));
	basicItems.push_back(new Log(-60, 40, g_heightMapTerrain));
	barrels.push_back(new Barrel(-60, -60, g_heightMapTerrain));
	barrels.push_back(new Barrel(-56, -54, g_heightMapTerrain));
	barrels.push_back(new Barrel(-43, 20, g_heightMapTerrain));
	basicItems.push_back(new CampFire(40, 60, g_heightMapTerrain));
	basicItems.push_back(new CampFire(-65, 68, g_heightMapTerrain));

	// Create mesh images
	basicMeshs.push_back(new Pillar(10, -60, g_heightMapTerrain));
	basicMeshs.push_back(new Pillar(10, -75, g_heightMapTerrain));
	basicMeshs.push_back(new Pillar(25, -60, g_heightMapTerrain));
	basicMeshs.push_back(new Pillar(25, -75, g_heightMapTerrain));
	basicMeshs.push_back(new Tree(30, 30, g_heightMapTerrain));
	basicMeshs.push_back(new Tree(30, 20, g_heightMapTerrain));
	basicMeshs.push_back(new Tree(30, 25, g_heightMapTerrain));
	basicMeshs.push_back(new DeadTree(100, 40, g_heightMapTerrain));
	boss.push_back(new BigSpider(35, -67, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(95, 95, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(100, 100, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-20, 70, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-25, 73, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-23, 80, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-40, 25, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-50, -50, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-54, -45, g_heightMapTerrain));
	enemies.push_back(new KillerAnt(-52, -47, g_heightMapTerrain));
	powerUps.push_back(new Heart(-67, 80, g_heightMapTerrain));
	powerUps.push_back(new Heart(5, -67, g_heightMapTerrain));
	powerUps.push_back(new FireArrow(-30, 20, g_heightMapTerrain));

	// Initailise intro screen class
	m_IntroScreen.init();
	m_endscreen.init();

	// initialise global variables 
	score = 0;
	health = 3;
	mMove = false;
	playerMass = 45;

	// Load a texture for the smoke trail
	fireParticleE.Initialise(MVector3f(40.0f, -1.31f, 61.0f), MVector3f(0, 20, 0), 1000, 0.01, 0.02);

	//start timer - time before player can take damage between two attacks 
	timeBetweenEffects.Start();

	// time between arrow attacks
	ArrowAttacks.Start();
} 

void UpdateScene(float dt)
{

	mMove = true;

	//if player in game 
	if (introScreen == false && endScreen == false){
		camera.Update(dt, jitter);							// Update the camera

		// update ants
		for(unsigned int i = 0; i < enemies.size(); i++){
			enemies[i]->Update(dt, camera.GetPosition(), g_heightMapTerrain);
		}
		// update spider
		for(unsigned int i = 0; i < boss.size(); i++){
			boss[i]->Update(dt, camera.GetPosition(), g_heightMapTerrain);
		}
		// update barrels
		for(unsigned int i = 0; i < barrels.size(); i++){
			barrels[i]->update(dt, g_heightMapTerrain);
		}
		// check for collsions
		CollisionDetection();
		// update the listener for FMOD
		g_audio.UpdateEventSound(camera);

		crossFadeRed.Update(dt);						// Update crossFade effect - will only do if active

		crossFadeWhite.Update(dt);						// Update white cross fade
		// update fire particle emitter
		fireParticleE.UpdateParticles(0.025f);
		// check for timer for fire arrows so pick up only active for 20 secs
		if(fireTimer.ElapsedTime() > 20){
			fire = false;
		}
		// update explosions
		for(unsigned int i = 0; i < explosions.size(); i++){
			explosions[i]->Update(dt);
		}
		// stop jitter if over a second
		if (jitterTime.ElapsedTime() > 1){
			jitter = false;
		}

	}	
	
	UpdateFrameRate(dt);						// Update the framerate (shown in titlebar)
}




void GameLoopVariable()
{

	// Start timer
	g_GameLoopTimer.Start();

	// Update game logic, physics, AI, etc.
	UpdateScene(dt);

	// Draw the scene
	RenderScene();

	// check if player is still alive
	if(health < 1){
		endScreen = true;
	}

	// Stop timer and save elapsed time 
	dt = g_GameLoopTimer.ElapsedTime();

}

WPARAM MainLoop()
{
	MSG msg;

	while(1)											// Do our infinate loop
	{													// Check if there was a message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        { 
			if(msg.message == WM_QUIT)					// If the message wasnt to quit
				break;
            TranslateMessage(&msg);						// Find out what the message does
            DispatchMessage(&msg);						// Execute the message
		}else{											// if there wasn't a message
		if (introScreen == true || endScreen ==true) {						//If we are on the intro screen only call renderscene
			RenderScene();								
		}else{		
			if (GetFocus() == g_hWnd) { //check if we have focus so we don't grab interrupt the mouse pointer for the debugger
				CameraKeys();								//Call camerakeys to detect movement
			}
			GameLoopVariable();						// Perform an iteration of the game loop
        } 
		}
	}

	DeInit();											// Clean up and free all allocated memory

	return(msg.wParam);									// Return from the program
}

void RenderScene() 
{			
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();	

	camera.Look(); // Call gluLookAt based on camera position, viewpoint and up vector

	MVector3f vPos	= camera.Position();
	MVector3f vView = camera.View();

	if (introScreen == true) {	//If we are on an introscreen
		// Render introscreen
		m_IntroScreen.Render(g_rRect);

		
	} 
	else if (endScreen == true){ // if on end screen
		// render endscreen
		m_endscreen.Render(g_rRect);
	}
	else {					// If in game

		// Draw the timer and skybox with lighting off
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_LIGHTING);
		text.Render(TimerText, 15, 25, GLUT_BITMAP_HELVETICA_18);  //Draw text for the timer
		sprintf_s(ScoreText, "Score: %d", score);//add the text plus the int score
		text.Render(ScoreText, g_rRect.right - 690, 25,  GLUT_BITMAP_HELVETICA_18 );
		sprintf_s(HealthText, "Health: %d", health);//add the text plus the int health
		text.Render(HealthText, 15, g_rRect.bottom - 315,  GLUT_BITMAP_HELVETICA_18 );
		if (fire == false) {
			sprintf_s(FireText, "Fire Arrow: N");//add the text plus depending on fire bool
			text.Render(FireText, g_rRect.right - 720, g_rRect.bottom - 315,  GLUT_BITMAP_HELVETICA_18 );
		}
		else {
			glColor3f(1.0, 0.0, 0.0);
			sprintf_s(FireText, "Fire Arrow: Y");//add the text plus depending on fire bool
			text.Render(FireText, g_rRect.right - 720, g_rRect.bottom - 315,  GLUT_BITMAP_HELVETICA_18 );
		}
		skyBox.Render(vPos.x,  vPos.y,  vPos.z, 250, 500, 250);
		glEnable(GL_LIGHTING);


		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		//Apply lighting effects
		lightingEffects.SetDefaultLighting(g_heightMapTerrain);

		// Apply material effects
		materialEffects.SetDefaultMaterial();
		

		if (g_terrainType == TERRAIN_PLANAR) {
			terrain.Render();
		} else if (g_terrainType == TERRAIN_HEIGHTMAP) {

			if (g_wireframe == true)
				glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );

			g_heightMapTerrain.Render(MVector3f(0, 0, 0), MVector3f(250, 25, 250));

			if (g_wireframe == true)
				glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
		}

		
		//Draw SecondaryObjects models
		for(unsigned int i = 0; i < basicMeshs.size(); i++){
			basicMeshs[i]->Render();
			//basicMeshs[i]->getBBox().Render(1, 0, 0);
		}

		for(unsigned int i = 0; i < arrows.size(); i++){
			arrows[i]->Render();
			//arrows[i]->getBBox().Render(1, 0, 0);
		}

		for(unsigned int i = 0; i < enemies.size(); i++){
			enemies[i]->Render(camera.GetPosition());
			//enemies[i]->getBBox().Render(1, 0, 0);
		}

		for(unsigned int i = 0; i < powerUps.size(); i++){
			powerUps[i]->Render();
			//powerUps[i]->getBBox().Render(1, 0, 0);
		}

		for(unsigned int i = 0; i < boss.size(); i++){
			boss[i]->Render();
			//boss[i]->getBBox().Render(1, 0, 0);
		}
			
		// Render basic objects
		for(unsigned int i = 0; i < basicItems.size(); i++){
			basicItems[i]->Render();
			//basicItems[i]->getBBox().Render(1, 0, 0);
		}

		for(unsigned int i = 0; i < barrels.size(); i++){
			barrels[i]->Render();
			//barrels[i]->getBBox().Render(1, 0, 0);
		}

		// render explosions
		for(unsigned int i = 0; i < explosions.size(); i++){
			explosions[i]->Render(camera.View()-camera.Position(), camera.UpVector(), 10, 10);
		}

		// Render cross fade effect - will only happen if active
		crossFadeRed.Render(1, 0, 0);
		crossFadeWhite.Render(1, 1, 1);
		// render particle effects
		fireParticleE.Render(camera.View()-camera.Position(), camera.UpVector());
	}
	SwapBuffers(g_hDC);									// Swap the backbuffers to the foreground
}

void CameraKeys(){

	
	// Once we have the frame interval, we find the current speed
	MVector3f speed = camera.getSpeed() * dt;

	if (introScreen == false && mMove){
		// Check if we hit the Up arrow or the 'w' key
		if((GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)) {	
			// Move our camera forward by a positive SPEED
			camera.MoveCamera(speed, g_heightMapTerrain);
			backwards = false;
		}
		// Check if we hit the Down arrow or the 's' key
		if((GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)) {	
			// Move our camera backward by a negative SPEED
			speed = speed * -1;
			camera.MoveCamera(speed, g_heightMapTerrain);
			backwards = true;
		}
		// Check if we hit the Left arrow or the 'a' key
		if((GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80)) {	
			// Strafe the camera left
			if(!(GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)){
				speed = speed * -1;
			}
			camera.StrafeCamera(speed, g_heightMapTerrain);
		}
		// Check if we hit the Right arrow or the 'd' key
		if((GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)) {			
			// Strafe the camera right
			if((GetKeyState(VK_DOWN) & 0x80 || (GetKeyState('S') & 0x80))){
				speed = speed * -1;
			}
			camera.StrafeCamera(speed, g_heightMapTerrain);
		}
	}
}


LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LONG    lRet = 0; 
    PAINTSTRUCT    ps;

    switch (uMsg)
	{ 
    case WM_SIZE:										// If the window is resized
		if(!g_bFullScreen)								// Do this only if we are NOT in full screen
		{
			SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));// LoWord=Width, HiWord=Height
			GetClientRect(hWnd, &g_rRect);					// Get the window rectangle
		}
        break; 
 
	case WM_CHAR:
		switch (wParam) {
			case '1': {
				if (introScreen == true){				//check if we are on the intro screen
					introScreen = false;
					g_audio.PlayMusicStream();
					timer.setMins(1);//set the minutes remaining
					timer.setSecs(59);
					TimerID = SetTimer(g_hWnd, AvatarTimer, 1000 , NULL);//Create the win32 timer
					char secs[26];//create a character array
					sprintf_s(TimerText, "Time Remaining: %d", timer.getMins());//add the text plus the int returned to the characted array
					sprintf_s(secs, ":%d", timer.getSecs());  //add the text plus the int returned to the characted array
					strcat_s(TimerText, secs);  //Add the two characted arrays together
				}
				else {
					// fire arrow based on camera position
					if(ArrowAttacks.ElapsedTime() > 1){
						MVector3f pos = camera.GetPosition();
						float x = pos.x;
						float y = pos.z;
						Arrow* arrow = new Arrow(x, y, g_heightMapTerrain);
						arrow->LaunchFromCamera(camera);
						arrows.push_back(arrow);
						ArrowAttacks.Start();
					}
				}
			}
			break;
			case '2': {
				if (introScreen == true){				//check if we are on the intro screen
					introScreen = false;
					g_audio.PlayMusicStream();
					timer.setMins(0);//set the minutes remaining
					timer.setSecs(59);
					TimerID = SetTimer(g_hWnd, AvatarTimer, 1000 , NULL);//Create the win32 timer
					char secs[26];//create a character array
					sprintf_s(TimerText, "Time Remaining: %d", timer.getMins());//add the text plus the int returned to the characted array
					sprintf_s(secs, ":%d", timer.getSecs());  //add the text plus the int returned to the characted array
					strcat_s(TimerText, secs);  //Add the two characted arrays together
				}
			}
			break;
		}
		break;
	case WM_PAINT:										// If we need to repaint the scene
		BeginPaint(hWnd, &ps);							// Init the paint struct		
		EndPaint(hWnd, &ps);							// EndPaint, Clean up
		break;

	case WM_KEYDOWN:
		switch(wParam) {								// Check if we hit a key
			case VK_ESCAPE:								// If we hit the escape key
				PostQuitMessage(0);						// Send a QUIT message to the window
				break;
			case VK_SPACE:								//If spacebar is pressed
				
				break;
			case VK_RETURN:
				break;
		}
		break;
 
    case WM_DESTROY:									// If the window is destroyed
        PostQuitMessage(0);								// Send a QUIT Message to the window
        break; 
     
	case WM_TIMER: //Check if a timer is triggered
		switch (wParam) 
		{ 
			case AvatarTimer://Check if the timer is avatartime
				if (timer.getMins() == 0 && timer.getSecs() == 0){//if time is up
					KillTimer(g_hWnd, TimerID);//destroy the timer
					// show end screen
					endScreen = true;
				} else if (timer.getSecs() == 0){//If seconds left is 0
					timer.setMins(-1);//Decrease minutes left by 1
					timer.setSecs(59);//Set seconds to 59
				} else {
					timer.setSecs(-1);//Decrement seconds left by 1
				}
				char secs[26];//Create a character array
				if (timer.getSecs() < 10){//if seconds left is less than 10
					sprintf_s(TimerText, "Time Remaining: %d", timer.getMins());//add string and int returned to the character array
					sprintf_s(secs, ":0%d", timer.getSecs());//add string and int returned to the character array
					strcat_s(TimerText, secs);//add the character arrays together
				} else {//Otherwise
					sprintf_s(TimerText, "Time Remaining: %d", timer.getMins());//add string and int returned to the character array
					sprintf_s(secs, ":%d", timer.getSecs());//add string and int returned to the character array
					strcat_s(TimerText, secs);//Add the character arrays together
				}
			break;
		} 
    default:											// Return by default
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
        break; 
    } 
    return lRet;										// Return by default
}

//detect any collisions between objects via a type of brute force 
void CollisionDetection()
{
	// for testing collsion detection
	MCollisionDetection MCD =  MCollisionDetection();

	// vectors used to remove items once finished with loop
	vector<int> removeArrows;
	vector<int> removeEnemies;
	vector<int> removeBarrels;
	vector<int> removePowerUp;
	vector<int> removeBoss;
	
	// check for collision with arrows
	for(unsigned int i = 0; i < arrows.size(); i++){
		arrows[i]->Update(dt);
		int errorstop = 0; 
		// escape bool to stop runtime errors
		bool escape = false;
		// if too low remove arrow
		float Ycoordinate = arrows[i]->getPosition().y;
		if(Ycoordinate < -10){
			removeArrows.push_back(i);
			break;
		}

		else{

			//if arrows collide with basic items 
			for(unsigned int j = 0; j < basicItems.size(); j++){
				if(MCD.DoBoxesIntersect(arrows[i]->getBBox(), basicItems.at(j)->getBBox())) {
					removeArrows.push_back(i);
					break;
					escape = true;
					errorstop+=1;
				}
			}

			if(escape){
				break;
			}
		
			//if arrows collide with normal meshes
			for(unsigned int j = 0; j < basicMeshs.size(); j++){
				if(MCD.DoBoxesIntersect(arrows[i]->getBBox(), basicMeshs.at(j)->getBBox())) {
					removeArrows.push_back(i);
					break;
					escape = true;
					errorstop+=1;
				}
			}

			if(escape){
				break;
			}

			//if arrows collide with enemies
			for(unsigned int j = 0; j < enemies.size(); j++){
				if(MCD.DoBoxesIntersect(arrows[i]->getBBox(), enemies.at(j)->getBBox())) {
					removeArrows.push_back(i);
					// play sound
					g_audio.PlayEventSound1(camera.GetPosition(), enemies.at(j)->getPosition());
					// work out score based on if using fire arrows and time between attacked enemies
					if(timeBetweenAttacks.ElapsedTime() < 3 && timeBetweenAttacks.ElapsedTime() > 0){
						if(fire == false) score += 20;
						else score += 40;
						timeBetweenAttacks.Start();
					}
					else{
						timeBetweenAttacks.Start();
						if(fire == false) score += 10;
						else score += 20;
					}

					if(enemies.at(j)->collisionReaction()){
						removeEnemies.push_back(j);
					}
					break;
					escape = true;
					errorstop+=1;
				}
			}

			if(escape){
				break;
			}

			//if arrows collide with barrels
			for(unsigned int j = 0; j < barrels.size(); j++){
				if(MCD.DoBoxesIntersect(arrows[i]->getBBox(), barrels.at(j)->getBBox())) {
					removeArrows.push_back(i);
					// if fire arrow is true
					if (fire == true){
						// activate cross fade
						crossFadeWhite.Activate();
						// activate jitter camera effect
						jitter = true;
						// play sound
						g_audio.PlayEventSound2(camera.GetPosition(), barrels.at(j)->getPosition());
						// start timer for jitter effect
						jitterTime.Start();
						// carry out barrel collision reaction
						barrels.at(j)->collisionReaction();
						// set up sprite explosion
						MVector3f pos = barrels.at(j)->getPosition();
						pos.y = pos.y + 2;
						SpriteExplosion* n = new SpriteExplosion(pos);
						n->Initialise("./Resources/Textures/explosion.tga", 4, 5, 16);
						n->Activate();
						explosions.push_back(n);
						removeBarrels.push_back(j);
					}
					break;
					escape = true;
					errorstop+=1;
				}
			}

			if(escape){
				break;
			}
			// if collides with spider
			for(unsigned int j = 0; j < boss.size(); j++){
				if(MCD.DoBoxesIntersect(arrows[i]->getBBox(), boss.at(j)->getBBox())) {
					removeArrows.push_back(i);
					// play sound
					g_audio.PlayEventSound1(camera.GetPosition(), boss.at(j)->getPosition());
					// work out score based on fire arrows and time between attacked enemies
					if(timeBetweenAttacks.ElapsedTime() < 3 && timeBetweenAttacks.ElapsedTime() > 0){
						if(fire == false) score += 40;
						else score += 80;
						timeBetweenAttacks.Start();
					}
					else{
						timeBetweenAttacks.Start();
						if(fire == false) score += 20;
						else score += 40;
					}
					// if has no health left remove
					if(boss.at(j)->collisionReaction()){
						removeBoss.push_back(j);
					}
					break;
					escape = true;
					errorstop+=1;
				}

			if(escape){
				break;
			}
			}
		}

		for(int k = 1; k < errorstop; k++){
			removeArrows.pop_back();
		}
	}

	//effects for collisions 
	for(unsigned int i = 0; i < removeArrows.size(); i++){
		arrows.erase(arrows.begin() + removeArrows.at(i));
	}

	for(unsigned int i = 0; i < removeEnemies.size(); i++){
		enemies.erase(enemies.begin() + removeEnemies.at(i));
	}

	for(unsigned int i = 0; i < removeBarrels.size(); i++){
		barrels.erase(barrels.begin() + removeBarrels.at(i));
	}

	for(unsigned int i = 0; i < removeBoss.size(); i++){
		boss.erase(boss.begin() + removeBoss.at(i));
	}

	//if player collides with basic object
	for(unsigned int i =0; i < barrels.size(); i++){
		if(MCD.DoBoxesIntersect(barrels[i]->getBBox(), camera.getBBox())){
			// if player weighs more than barrel then barrel is pushes along
			if(playerMass > barrels[i]->getMass()){
				MVector3f tempSpeed = camera.getSpeed() * dt;
				MVector3f tempDirection =barrels[i]->getPosition() - camera.GetPosition();
				tempDirection.Normalize();
				barrels[i]->setVelocity(tempDirection+=tempSpeed);
			}
		}
	}
	
	//if the player walks into a basic item 
	for(unsigned int i =0; i < basicItems.size(); i++){
		if(MCD.DoBoxesIntersect(basicItems[i]->getBBox(), camera.getBBox())){
			// if player weighs less than an object then bounces off of it
			if(playerMass <= basicItems[i]->getMass()){
				MVector3f tempSpeed = camera.getSpeed() * dt;
				MVector3f tempDirection = camera.GetPosition() - basicItems[i]->getPosition();
				tempDirection.Normalize();
				if(!backwards){
					tempDirection = tempDirection * -1;
				}
				camera.MoveCamera((tempDirection += tempSpeed), g_heightMapTerrain);
			}
		}
	}

	//if player walks into a mesh
	for(unsigned int i =0; i < basicMeshs.size(); i++){
		if(MCD.DoBoxesIntersect(basicMeshs[i]->getBBox(), camera.getBBox())){
			//bounces off of it
			MVector3f tempSpeed = camera.getSpeed() * dt;
			MVector3f tempDirection = camera.GetPosition() - basicMeshs[i]->getPosition();
			tempDirection.Normalize();
			if(!backwards){
				tempDirection = tempDirection * -1;
			}
			camera.MoveCamera((tempDirection += tempSpeed), g_heightMapTerrain);
		}
	}

	//if player walks through a power up
	for(unsigned int i =0; i < powerUps.size(); i++){
		if(MCD.DoBoxesIntersect(powerUps[i]->getBBox(), camera.getBBox()) && powerUps[i]->collisionReaction()){
			// if heart gains health
			health += 1;
			// play audio
			g_audio.PlayEventSound3(camera.GetPosition(), powerUps.at(i)->getPosition());
			removePowerUp.push_back(i);
		}
		else if (MCD.DoBoxesIntersect(powerUps[i]->getBBox(), camera.getBBox())){
			// if fire arrow gain fire arrow ability for 20 secs
			fire = true;
			fireTimer.Start();
			// play sound
			g_audio.PlayEventSound3(camera.GetPosition(), powerUps.at(i)->getPosition());
			removePowerUp.push_back(i);
		}
	}

	for(unsigned int i = 0; i < removePowerUp.size(); i++){
		powerUps.erase(powerUps.begin() + removePowerUp.at(i));
	}

		//if player walks through an enemy
	for(unsigned int i =0; i < enemies.size(); i++){
		if(MCD.DoBoxesIntersect(enemies[i]->getBBox(), camera.getBBox()) && timeBetweenEffects.ElapsedTime() > 2){
			// player losses health and cross fade and jitter effect start
			health -= 1;
			crossFadeRed.Activate();
			jitter = true;
			timeBetweenEffects.Start();
			jitterTime.Start();
		}
	}
	 
	for(unsigned int i =0; i < boss.size(); i++){	
		if(MCD.DoBoxesIntersect(boss[i]->getBBox(), camera.getBBox()) && timeBetweenEffects.ElapsedTime() > 2){
			// player losses health and cross fade and jitter effect start
			health -= 1;
			crossFadeRed.Activate();
			jitter = true;
			timeBetweenEffects.Start();
			jitterTime.Start();
		}

		if (boss[i]->ProjectileCollision(camera.getBBox()) == true && timeBetweenEffects.ElapsedTime() > 2){
			// player losses health and cross fade and jitter effect start
			health -= 1;
			crossFadeRed.Activate();
			jitter = true;
			timeBetweenEffects.Start();
			jitterTime.Start();
		}
	}
}

