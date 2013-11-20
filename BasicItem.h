#pragma once
#include "MVector3f.h"
#include "MBoundingBox.h"
#include "MHeightMapTerrain.h"

// base class for basic items in game not made from meshes

class BasicItem
{
public:
	// constructor
	BasicItem(void);
	// deconstructor
	~BasicItem(void);
	// virtual render method
	virtual void Render(void);
	// virtual collision reation method
	virtual bool collisionReaction(void);
	// method to return bounding box
	MBoundingBox getBBox();
	// returns mass of item
	float getMass();
	// returns position of item
	MVector3f getPosition();
	// method to set position of item
	void setPosition(MVector3f speed, MHeightMapTerrain &g);
private:
	// represents position of item
	MVector3f m_vPosition;
protected:
	// bounding box of item
	MBoundingBox bBox;
	// mass of item
	float objectMass;

};

