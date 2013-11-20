#include "FireArrow.h"


FireArrow::FireArrow(void)
{
}


FireArrow::FireArrow(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y + 0.5;
	// Load mesh
	m_mesh.Load("./Resources/3DS/arrow_low_poly.3ds");

	//set custom bounding box on arrow head
	bBox.FitToMesh(&m_mesh);
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - (dx/2) + 0.5;
	minPoint.y = m_position.y;
	minPoint.z = m_position.z - (dz/2) + 1.5;
	MVector3f maxPoint;
	maxPoint.x = m_position.x + (dx/2) - 0.5;
	maxPoint.y = m_position.y + (dy * 0.07);
	maxPoint.z = m_position.z + (dz/2) - 0.5;
	bBox.Set(minPoint, maxPoint);
}


FireArrow::~FireArrow(void)
{
}

void FireArrow::Render(void)
{

	glPushMatrix();
		// Move into position
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glColor3f(1, 0, 0);
		glRotatef(45, 1, 0, 0);
		glScalef(0.1, 0.1, 0.1);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}
