#pragma once
#include "MVector3f.h"
#include "MBoundingBox.h"

class MCollisionDetection
{
public:
	MCollisionDetection();
	~MCollisionDetection();
	bool DoBoxesIntersect(MBoundingBox box1, MBoundingBox box2);
	
private:
	
};


