#include "EnemyProjectile.h"


EnemyProjectile::EnemyProjectile(void)
{
	m_mass = 0.425f; // in kg
	m_rotationalInertia = (2.0f/3.0f) * m_mass * 0.5f * 0.5f; // in kg m^2
	m_coefficientOfRestitution = 0.55f; // percentage
	m_contactTime = 0.05f; // in seconds

	// Set texture 
	MTexture texture;
	texture.CreateFromBMP(&spiderTexture, "Resources/Textures/spider.bmp");
}


EnemyProjectile::~EnemyProjectile(void)
{
}

void EnemyProjectile::Launch(MVector3f target, MVector3f startPos)
{
	//set direction where projectile will start with 
	MVector3f direction = target - startPos;
	direction.y = 15.0f;
	direction.Normalize();

	//set various things needed to determine force, acceleration, resistance and velocity
	position = startPos;
	velocity = MVector3f(0.0f, 0.0f, 0.0f);
	m_acceleration = MVector3f(0.0f, -9.8f, 0.0f);
	m_instantaneousAcceleration = MVector3f(0.0f, 0.0f, 0.0f);
	m_angle = MVector3f(0.0f, 0.0f, 0.0f);
	m_angularVelocity = MVector3f(0.0f, 0.0f, 0.0f);
	m_angularAcceleration = MVector3f(0.0f, 0.0f, 0.0f);
	m_instantaneousAngularAcceleration = MVector3f(0.0f, 0.0f, 0.0f);
	m_contactTime = 0.0f;

	// m_velocity = 25.0f * direction;
	MVector3f force = direction * 70.0f;
	m_instantaneousAcceleration = force / m_mass;

	//force torque 
	MVector3f torque = 200 * MVector3f(1, 0, 0);
	m_instantaneousAngularAcceleration = torque / m_rotationalInertia;

	//set the rotation force so that projectiles spin
	m_theta = 90.0f - (180.0f / 3.141529f) * acos(direction.y);
	m_phi = (180.0f / 3.1415290f) * atan2(direction.x, direction.z);

	// setup boundingbox 
	MVector3f minPoint(0.5f, 0.5f, 0.5f);
	minPoint = position - minPoint;
	MVector3f maxPoint(0.5f, 0.5f, 0.5f);
	maxPoint = position + maxPoint;
	bBox.Set(minPoint, maxPoint);
	objectMass = 5;
}

void EnemyProjectile::Update(float dt, MHeightMapTerrain &g)
{
	//start altering it's velocity and position
	m_lastPosition = position;
	position += velocity * dt;
	bBox.Translate((velocity * dt));
	velocity += (m_acceleration + m_instantaneousAcceleration) * dt;

	//determin it's rotation based on time
	m_angle += m_angularVelocity * dt;
	m_angularVelocity += (m_angularAcceleration + m_instantaneousAngularAcceleration) * dt; 

	// Turn off instantaneous forces if contact time is surpassed
	if (m_instantaneousAcceleration.Length() > 0 && m_contactTime > 0.05) {
		m_instantaneousAcceleration = MVector3f(0, 0, 0);
		m_instantaneousAngularAcceleration = MVector3f(0, 0, 0);
		m_contactTime = 0;
	}
	m_contactTime += dt;

	// Check for collision detection
	float yPlane = 0.0f;
	if (CollisionDetection(g)) {
		CollisionResponse();
	}
	
}


void EnemyProjectile::Render()
{
	glPushMatrix();
		// Move to want position
		glTranslatef(position.x, position.y, position.z);

		glRotatef(m_phi, 0, 1, 0);
		glRotatef(-m_theta, 1, 0, 0);
		if (m_angle.Length() > 0)
			glRotatef(m_angle.Length(), m_angle.x, m_angle.y, m_angle.z);	// Rotate the ball resulting from torque

		// Create quadric for making cylinder
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		// Sort out texture and colour
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, spiderTexture);
		gluQuadricTexture(quadratic, GL_TRUE);
		gluSphere(quadratic, 0.5, 20, 20);
	glPopMatrix();
	objectMass = 10;
}

bool EnemyProjectile::CollisionDetection(MHeightMapTerrain &g){

	float ground = g.ReturnGroundHeight(position); 
		// Check for collision with the ground by looking at the y value of the ball's position
	if (position.y - 0.5 < ground) {
		return true;
	}
	return false;

}

void EnemyProjectile::CollisionResponse(){
		float convergenceThreshold = 1.5f;
	if (velocity.Length() > convergenceThreshold) {
		// The ball has bounced!  Implement a bounce by flipping the y velocity.
		velocity = MVector3f(velocity.x, -velocity.y, velocity.z);

		velocity *= 0.8f;
		m_angularVelocity *= 0.8f;

	}
}

bool EnemyProjectile::isNotMoving(){
	//if the ball has stoped moving beyond a certain threshold remove it form game
	if((velocity.x < 0.1f && velocity.z < 0.1f) || (velocity.x > -0.1f && velocity.z > -0.1f)){
		return true;
	}
	else return false;
}