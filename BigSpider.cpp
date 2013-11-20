#include "BigSpider.h"


BigSpider::BigSpider(void)
{
}

BigSpider::BigSpider(int x, int z, MHeightMapTerrain &g_heightMapTerrain)
{
	// Set x and z position
	m_position.x = (float)x;
	m_position.z = (float)z;
	// Get the terrain hight and yet as y
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y + 2;
	
	// Load mesh
	m_mesh.Load("./Resources/3DS/spider.3ds");
	health = 6;

	//set bounding box
	bBox.FitToMesh(&m_mesh);
	float dx, dy, dz;
	MVector3f centre;
	bBox.GetSizeAndCentre(dx, dy, dz, centre);
	MVector3f minPoint;
	minPoint.x = m_position.x - ((dx/2) * 2) + 4;
	minPoint.y = m_position.y - (dy);
	minPoint.z = m_position.z - ((dz/2) * 2);
	MVector3f maxPoint;
	maxPoint.x = m_position.x + ((dx/2) * 2) - 3;
	maxPoint.y = m_position.y + (dy);
	maxPoint.z = m_position.z + ((dz/2) * 2);
	bBox.Set(minPoint, maxPoint);

	//set velocity
	velocity = MVector3f(0, 0, 0);
	maxAcceleration = 4;

	//set it to wait for player to get close
	state = WAIT;
}

BigSpider::~BigSpider(void)
{
	//destructor
}

void BigSpider::Render(void)
{
	glPushMatrix();
		// Move into position
		glTranslatef((m_position.x + 2), m_position.y, (m_position.z - 2));

		//rotate based on player position
		glRotatef(angle, 0, 1, 0); 
		glScalef(2, 2, 2);
		glColor3f(0.7, 0.5, 0.5);
		// draw to screen
		m_mesh.Draw();
	glPopMatrix();

	//render the spider attacks
	for(unsigned int i = 0; i < projectiles.size(); i++){
		projectiles[i]->Render();
		//projectiles[i]->getBBox().Render(1, 0, 0);
	}
}

bool BigSpider::collisionReaction(void)
{
	//reduce health if spider collides with player attack
	health = health - 1;
	
	//if the spider has no health it dies
	if (health > 0){
		return false;
	}
	else return true;
}

void BigSpider::Update(float dt, MVector3f enemyPosition, MHeightMapTerrain &g_heightMapTerrain)
{
	//create a new attack to be ready
	MVector3f dist;

	//set direction it should go should it see player
	dist.x = m_position.x - enemyPosition.x;
	dist.z = m_position.z - enemyPosition.z;

	// a is distance from player 
	float a = sqrt((dist.x*dist.x) + (dist.z* dist.z));

	//random number for firing projectiles
	int r = rand()%100;
	
	switch (state) { 
		case WAIT : 
			velocity = MVector3f(0, 0, 0);

			//if player gets too close it starts to move
			if (a < 50){
				state = MOVE;
			}
			break;
			//state machine for movement; get closer and attack
		case MOVE : 
			velocity = movement.Seek(enemyPosition, m_position, velocity, maxAcceleration);

			if (a > 50 ){
				state = WAIT;
			}
			if (a < 10){
				state = ARRIVE;
			}
			if (health <= 1){
				state = FLEE;
			}
			if (r < 5){
				state = ATTACK;
			}
			//set angle it should be facing in regards to player
			angle =((180 / 3.141529) * atan2(direction.x, direction.z));
			break;
		//state machine when spider gets close, it will attack with projectiles when closer
		case ARRIVE :
			velocity = movement.Arrive(enemyPosition, 2, m_position, velocity, maxAcceleration);
			if (a >= 10){
				state = MOVE;
			}
			if (health <= 1){
				state = FLEE;
			}
			if (r <= 5){
				state = ATTACK;
			}
			angle = ((180 / 3.141529) * atan2(direction.x, direction.z));
			break; 

			//spider opens fire upon player
		case ATTACK :
			Fire(enemyPosition);
			if (health <= 1){
				state = FLEE;
			}
			else {
				state = MOVE;
			}
			angle = ((180 / 3.141529) * atan2(direction.x, direction.z));
			break;

			//cowardly runs away, facing away from player
		case FLEE : 
			velocity = movement.Flee(enemyPosition, m_position, velocity, maxAcceleration);
			if (a > 50){
				state = WAIT;
			}
			if (r < 5){
				state = ATTACK;
				 
			}
			angle = 180 + ((180 / 3.141529) * atan2(direction.x, direction.z));
			break;
	}

	//move in regards to velocity
	float temp = m_position.y;
	m_position += velocity * (dt);
	
	//set height in regards to terrain
	float y = g_heightMapTerrain.ReturnGroundHeight(m_position);
	m_position.y = y + 2;

	//set x,yz for bounding box
	temp = (y + 2) - temp;
	velocity.y = 0;
	bBox.Translate((velocity * dt));
	bBox.TranslateY(temp);

	//finalise direction
	direction = enemyPosition - m_position;
	direction.Normalize();

	//remove any projectiles which hit player
	vector<int> removeProjectile;

	for(unsigned int i = 0; i < projectiles.size(); i++){
		projectiles[i]->Update(dt, g_heightMapTerrain);
		if(projectiles[i]->isNotMoving()){
			removeProjectile.push_back(i);
			break;
		}
	}

	for(unsigned int i = 0; i < removeProjectile.size(); i++){
		projectiles.erase(projectiles.begin() + removeProjectile.at(i));
	}
}

void BigSpider::Fire(MVector3f enemyPosition)
{
	//create a new attack and fire in regards to player
	EnemyProjectile* pro = new EnemyProjectile();
	pro->Launch(enemyPosition, m_position);
	projectiles.push_back(pro);
}

bool BigSpider::ProjectileCollision(MBoundingBox bbox)
{
	MCollisionDetection MCD =  MCollisionDetection();

	vector<int> removeProjectile;
	bool result;

	result = false;

	for(unsigned int i = 0;i < projectiles.size(); i++){
		if(MCD.DoBoxesIntersect(projectiles[i]->getBBox(), bbox)){
			result = true;
		}
	}

	for(unsigned int i = 0; i < removeProjectile.size(); i++){
		projectiles.erase(projectiles.begin() + removeProjectile.at(i));
	}

	return result;

}