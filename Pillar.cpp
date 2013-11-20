#include "Pillar.h"


Pillar::Pillar(void)
{
}

Pillar::Pillar(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y - 5;
	// Load mesh
	m_mesh.Load("./Resources/3DS/pillar.3ds");
	bBox.FitToMesh(&m_mesh);
	//bounding box resized for more realistic effect
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - ((dx/2) * 0.025);
	minPoint.y = m_position.y;
	minPoint.z = m_position.z - ((dz/2) * 0.025);
	MVector3f maxPoint;
	maxPoint.x = m_position.x + ((dx/2) * 0.025);
	maxPoint.y = m_position.y + (dy * 0.059);
	maxPoint.z = m_position.z + ((dz/2) * 0.025);
	bBox.Set(minPoint, maxPoint);

}

Pillar::~Pillar(void)
{
}

void Pillar::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_position.x, m_position.y, m_position.z);
		// Scale to size
		glScalef(0.05, 0.04, 0.05);
		glColor3f(1, 1, 1);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}
