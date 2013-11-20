#include "MCollisionDetection.h"

MCollisionDetection::MCollisionDetection()
{}

MCollisionDetection::~MCollisionDetection()
{}

bool MCollisionDetection::DoBoxesIntersect(MBoundingBox box1, MBoundingBox box2)
{
	float width1, height1, depth1, width2, height2, depth2;
	MVector3f centre1, centre2;
	box1.GetSizeAndCentre(width1, height1, depth1, centre1);
	box2.GetSizeAndCentre(width2, height2, depth2, centre2);

	MVector3f v = centre2 - centre1;
	if (fabs(v.x) * 2 <= (width1 + width2) && 
        fabs(v.y) * 2 <= (height1 + height2) && 
        fabs(v.z) * 2 <= (depth1 + depth2))
		return true; // Collision detected
	else
		return false; // No collision detected
}




