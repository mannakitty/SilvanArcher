#include "Tree.h"


Tree::Tree(void)
{
}


Tree::Tree(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y;
	// Load mesh
	m_mesh.Load("./Resources/3DS/fir4_3ds/firtree4.3ds");
	//bounding box resized for more realistic effect
	bBox.FitToMesh(&m_mesh);
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - ((dx/2) * 0.25);
	minPoint.y = m_position.y;
	minPoint.z = m_position.z - ((dz/2) * 0.25);
	MVector3f maxPoint;
	maxPoint.x = m_position.x + ((dx/2) * 0.25);
	maxPoint.y = m_position.y + (dy * 1.5);
	maxPoint.z = m_position.z + ((dz/2) * 0.25);
	bBox.Set(minPoint, maxPoint);
}

Tree::~Tree(void)
{
}

void Tree::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_position.x, m_position.y, m_position.z);
		// Rotate
		glRotatef(45, 0, 1, 0);
		// Scale
		glScalef(1.5, 1.5, 1.5);
		glColor3f(1, 1, 1);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}