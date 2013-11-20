#pragma once
#include"MVector3f.h"
#include "MCamera.h"

// class to represent different movement methods avalable to enemies

class Movement
{
public:
	// constructor
	Movement(void);
	// deconstructor
	~Movement(void);
	// moves enemy towards current player position
	MVector3f Seek(MVector3f target, MVector3f position, MVector3f velocity, float maxAcceleration);
	// moves away from current player position
	MVector3f Flee(MVector3f target, MVector3f position, MVector3f velocity, float maxAcceleration);
	// slows down velocity as arrives at player position
	MVector3f Arrive(MVector3f target, int deceleration, MVector3f position, MVector3f velocity, float maxAcceleration);
};

