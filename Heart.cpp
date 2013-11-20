#include "Heart.h"


Heart::Heart(void)
{
}

Heart::Heart(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y + (float)2.5;
	// Load mesh
	m_mesh.Load("./Resources/3DS/coracao partido.3ds");
	bBox.FitToMesh(&m_mesh);
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - (dx/2)+ (float)0.8;
	minPoint.y = m_position.y- (dz/2) -1;
	minPoint.z = m_position.z - 2;
	MVector3f maxPoint;
	maxPoint.x = m_position.x + (dx/2) + 1;
	maxPoint.y = m_position.y + (dz/2) -1;
	maxPoint.z = m_position.z + dy - 1;
	bBox.Set(minPoint, maxPoint);
}


Heart::~Heart(void)
{
}

void Heart::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(-90, 1, 0, 0);
		// Set colour of heart
		glColor3f(1, 0, 0);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}

//return true if player collides with it 
bool Heart::collisionReaction()
{
	return true;
}
