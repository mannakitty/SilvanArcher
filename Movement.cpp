#include "Movement.h"


Movement::Movement(void)
{
}


Movement::~Movement(void)
{
}

MVector3f Movement::Seek(MVector3f target, MVector3f position, MVector3f velocity, float maxAcceleration)
{
	//create velocity towards target
	MVector3f desiredVelocity = target - position;
	desiredVelocity.Normalize();
 	desiredVelocity = desiredVelocity * maxAcceleration;
	desiredVelocity = desiredVelocity;
	return desiredVelocity;
}

MVector3f Movement::Flee(MVector3f target, MVector3f position, MVector3f velocity, float maxAcceleration)
{
	//create velocity away from target
	MVector3f desiredVelocity = position - target;
	desiredVelocity.Normalize();
	desiredVelocity = desiredVelocity * maxAcceleration;
	desiredVelocity = desiredVelocity;

	return desiredVelocity;
}
 
MVector3f Movement::Arrive(MVector3f target, int deceleration, MVector3f position, MVector3f velocity, float maxAcceleration)
{
	//slow down velocity based on distance from target 
	MVector3f distence = target - position;
	float dist = distence.Length();

	if (dist > 0){
		double decelerationTweak = 0.3;
		double speed = dist/(deceleration*decelerationTweak);
		speed = min(speed, maxAcceleration);
		MVector3f desiredVelocity;
		desiredVelocity = distence * speed/dist;
		desiredVelocity = desiredVelocity - velocity;

		return desiredVelocity;
	}

	return MVector3f(0, 0, 0);
}
