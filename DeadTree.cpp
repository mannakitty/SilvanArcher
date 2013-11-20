#include "DeadTree.h"


DeadTree::DeadTree(void)
{
}


DeadTree::DeadTree(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y;
	// Load mesh
	m_mesh.Load("./Resources/3DS/tree.3ds");

	//set mesh to custom size rather than auto
	bBox.FitToMesh(&m_mesh);
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - (4/2);
	minPoint.y = m_position.y;
	minPoint.z = m_position.z - (4/2);
	MVector3f maxPoint;
	maxPoint.x = m_position.x + (4/2);
	maxPoint.y = m_position.y + (10);
	maxPoint.z = m_position.z + (4/2);
	bBox.Set(minPoint, maxPoint);
}


DeadTree::~DeadTree(void)
{
}

void DeadTree::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_position.x, m_position.y, m_position.z);
		// Set colour of heart
		glColor3f(0.5, 0.3, 0.3);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}
