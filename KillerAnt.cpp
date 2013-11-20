#include "KillerAnt.h"


KillerAnt::KillerAnt(void)
{
}

KillerAnt::KillerAnt(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	meshDirection.x = 0;
	meshDirection.y = 0;
	meshDirection.z = 1;
	meshDirection.Normalize();
	angle = 0;
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y;
	// Load mesh
	m_mesh.Load("./Resources/3DS/ant.3ds");
	//set health to one as a week enemy
	health = 1;

	bBox.FitToMesh(&m_mesh);
	defaultBox.FitToMesh(&m_mesh);
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	defaultBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - ((dx/2) * 2) + 0.5;
	minPoint.y = m_position.y;
	minPoint.z = m_position.z - ((dz/2) * 2) - 1.5;
	MVector3f maxPoint;
	maxPoint.x = m_position.x + ((dx/2) * 2) ;
	maxPoint.y = m_position.y + (dy * 2);
	maxPoint.z = m_position.z + ((dz/2) * 2) - 1;
	bBox.Set(minPoint, maxPoint);
	defaultBox.Set(minPoint, maxPoint);

}

KillerAnt::~KillerAnt(void)
{
	//destructor
}

void KillerAnt::Render(MVector3f me)
{
	glPushMatrix();
		// Move into position
		glTranslatef((m_position.x + 1 ), m_position.y,( m_position.z -1));

		//rotate to face player
		glRotatef(angle, 0, 1, 0);
		glScalef(2, 2, 2);
		glColor3f(0.8, 0.8, 0.8);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}

bool KillerAnt::collisionReaction(){

	//every collision reduces it's health
	health = health - 1;
	
	//if health < = 0 it will die
	if (health > 0){
		return false;
	}
	else return true;
}

void KillerAnt::Update(float dt, MVector3f m, MHeightMapTerrain &g_heightMapTerrain)
{
	// setting the bouning box

	//set the angle of the ant will be facing 
    angle = 270 + ((180 / 3.141529) * atan2(direction.x, direction.z));

	//set new position based on velocity 
	float temp = m_position.y;
	m_position += velocity * (dt);
	
	//set hieght based off hieght map
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y;

	temp = y - temp;
	velocity.y = 0;
	
	//move bounding box based on velocity
	defaultBox.Translate((velocity * dt)); 
	defaultBox.TranslateY(temp);
	
	//displayer bounding box
	bBox.Set(defaultBox.returnMinPoint(), defaultBox.returnMaxPoint());


	direction = m - m_position;
	direction.Normalize();

	velocity = 2*direction;
}

MVector3f KillerAnt::getPosition()
{
	// return the position of ant
	return m_position;
}