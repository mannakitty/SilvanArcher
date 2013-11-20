#include "BasicMesh.h"


BasicMesh::BasicMesh(void)
{
	//basic constructor 
}


BasicMesh::~BasicMesh(void)
{
	//basic destructor
}

void BasicMesh::Render(MVector3f me)
{
	//render interface method
}

void BasicMesh::Render()
{
	//render interface method
}

bool BasicMesh::collisionReaction(void)
{
	//default reaction to a collision is no reaction
	return false;
}

MBoundingBox BasicMesh::getBBox()
{
	//return the bounding box
	return bBox;
}

void BasicMesh::Update(float dt, MVector3f n, MHeightMapTerrain &g_heightMapTerrain)
{
	//update object based of parameters
}

MVector3f BasicMesh::getPosition()
{
	//return the position of mesh
	return m_position;
}