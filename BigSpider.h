#pragma once
#include <windows.h>
#include "BasicMesh.h"
#include "MVector3f.h"
#include "MCamera.h"
#include "MModel_3DS.h"
#include "MHeightMapTerrain.h"
#include "./include/glut.h"
#include "Movement.h"
#include "EnemyProjectile.h"
#include "MCollisionDetection.h"

using namespace std;

// Class to represent enemy boss in game

// enumerator for different states of spider
enum {
WAIT,
MOVE,
ARRIVE,
ATTACK,
FLEE
};

class BigSpider : public BasicMesh
{
public:
	// Constructor
	BigSpider();
	BigSpider(int x, int z, MHeightMapTerrain &g_heightMapTerrain);
	// Deconstructor
	~BigSpider();
	// render spider to screen
	void Render();
	// collision reaction method
	bool collisionReaction();
	// updates spider position and behaviour
	void Update(float dt, MVector3f enemyPosition, MHeightMapTerrain &g_heightMapTerrain);
	// method to fire projectile towards player
	void Fire(MVector3f enemyPosition);
	// method to check collisions
	bool ProjectileCollision(MBoundingBox bbox);
private:
	// stores position of spider
	MVector3f m_position;
	// Stores mesh of spider
	MModel_3DS m_mesh;
	// Strores health of spider
	int health;
	// Stores the state of the spider
	int state;
	// Velocity of spider
	MVector3f velocity;
	// Direction spider is heading in
	MVector3f direction;
	// Movement methods for spider
	Movement movement;
	// Max acceleration
	float maxAcceleration;
	// Vector of projectiles
	vector<EnemyProjectile*> projectiles;
	//direction spider should be facing in regards to player
	float angle;
};
