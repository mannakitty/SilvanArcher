#pragma once
#include "MVector3f.h"
#include "MModel_3DS.h"
#include "MBoundingBox.h"
#include "MHeightMapTerrain.h"

// Class to represent basic objects made from meshes in the game

class BasicMesh
{
public:
	// Constructor
	BasicMesh(void);
	// Deconstructor
	~BasicMesh(void);
	// Virtual render method
	virtual void Render(MVector3f me);
	// secondary virtual render method
	virtual void Render(void);
	// virtual collision reaction method
	virtual bool collisionReaction(void);
	// virtual update method
	virtual void Update(float dt, MVector3f n, MHeightMapTerrain &g_heightMapTerrain);
	// returns bounding box
	MBoundingBox getBBox();
	// virtual return position
	virtual MVector3f getPosition();
private:
	// position of object
	MVector3f m_position;
	// 3d mesh of object
	MModel_3DS m_mesh;
protected:
	// bounding box of object
	MBoundingBox bBox;
};

