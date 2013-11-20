#pragma once
#include "BasicItem.h"
#include "MVector3f.h"
#include "MTexture.h"
#include "MHeightMapTerrain.h"

// Class to represent an enemy projectile

class EnemyProjectile : public BasicItem
{
public:
	// constructor
	EnemyProjectile(void);
	// deconstructor
	~EnemyProjectile(void);
	// update method for projectile
	void Update(float dt, MHeightMapTerrain &g);
	// render method for projectile
	void Render();
	// launch from spider
	void Launch(MVector3f target, MVector3f startPos);
	// collision responce method
	void CollisionResponse(void);
	// collsion detection method
	bool CollisionDetection(MHeightMapTerrain &g);
	// to check if projectile is still moving or not
	bool isNotMoving();
private:
	// stores position of projectile
	MVector3f position;
	// store velocity of projectile
	MVector3f velocity;
	// stores acceleration of projectile
	MVector3f m_acceleration;
	// stores instant acceleration of projectile
	MVector3f m_instantaneousAcceleration;
	// store last position of projectile
	MVector3f m_lastPosition;
	
	float m_mass; // in kg
	float m_rotationalInertia; // in kg m^2
	float m_contactTime; // in seconds
	float m_coefficientOfRestitution; // as a percentage
	float m_radius; // radius of ball in meters

	float m_theta ;
	float m_phi ;

	// Rotational physical quantities
	MVector3f m_angle;
	MVector3f m_angularVelocity;
	MVector3f m_angularAcceleration;
	MVector3f m_instantaneousAngularAcceleration;

	// texture of projectile
	GLuint spiderTexture;

};

