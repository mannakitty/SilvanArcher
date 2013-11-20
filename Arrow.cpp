#include "Arrow.h"


Arrow::Arrow(void)
{
}


Arrow::Arrow(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y;
	// Load mesh
	m_mesh.Load("./Resources/3DS/arrow_low_poly.3ds");
	// fit bounding box to the mesh
	bBox.FitToMesh(&m_mesh);
	
}

Arrow::~Arrow(void)
{
}

void Arrow::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glColor3f(1, 1, 1);
		glRotatef(m_phi, 0, 1, 0);
		glRotatef(m_theta, 1, 0, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(0.05, 0.05, 0.05);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();
}

void Arrow::Update(float dt)
{
	// remove gravity from the arrows velocity
	m_velocity -= gravity;

	//this rotated the arrow but caused too much lag to stay  
	/* 
	float alpha = (180 / 3.141529) * acos(m_velocity.y);
	m_theta = 90 + alpha;

	glRotatef(m_theta, 1, 0, 0);
	*/

	//gradual loss of acceleration 
	acceleration -= acceleration * 0.6;

	// stops arrow coming back to player
	if ((m_velocity.x > 0) && (m_velocity.z > 0) ){
		m_velocity -= acceleration;
	}
	// update position based on velocity
	m_position += m_velocity * dt;
	//update bounding box position
	bBox.Translate((m_velocity * dt));

}

void Arrow::LaunchFromCamera(MCamera camera)
{
	MVector3f cameraPos = camera.GetPosition();
	MVector3f viewPoint = camera.View();
	MVector3f direction = viewPoint - cameraPos; // Direction camera is facing
	direction.Normalize(); // Normalised direction, dhat

	//Acceleration = force divided by mass (force being the direction 
	acceleration = (direction * 2) / 0.22;

	// set position to be same as camera
	m_position = camera.GetPosition();
	// set velocity
	m_velocity = direction * 25;

	// get angles neede to rotate arrow by to be facing right way
	float alpha = (180 / 3.141529) * acos(direction.y);
	m_theta = 90 + alpha;
	m_phi = (180 / 3.141529) * atan2(direction.x, direction.z);
	// reposition bounding box around arrow head
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - ((dz/2) * 0.05);
	minPoint.y = m_position.y - ((dx/2) * 0.05);
	minPoint.z = m_position.z;
	MVector3f maxPoint;
	maxPoint.x = m_position.x + ((dz/2) * 0.05);
	maxPoint.y = m_position.y + ((dx/2) * 0.05);
	maxPoint.z = m_position.z;
	bBox.Set(minPoint, maxPoint);

	// mass of arrow
	mass = 0.01;
	// set gravity
	gravity = MVector3f(0.0f, 9.81f, 0.0f);
	gravity *= mass;
}

void Arrow::Initialise()
{
	// load mesh from memory
	m_mesh.Load("./Resources/3DS/arrow_low_poly.3ds");

}

MVector3f Arrow::getPosition(void){
	// return position of arrow
	return m_position;
}