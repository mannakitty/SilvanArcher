#include "BasicItem.h"


BasicItem::BasicItem(void)
{	
	//setbasic mass to zero 
	objectMass = 0;
}


BasicItem::~BasicItem(void)
{
	//destructor
}

void BasicItem::Render(void)
{
	//render method. interface layer
}

bool BasicItem::collisionReaction(void)
{
	//basic objects never have a reaction so always return false
	return false;
}

MBoundingBox BasicItem::getBBox()
{
	
	//return bounding box of item
	return bBox;
}

float BasicItem::getMass()
{	
	//return mass of object
	return objectMass;
}

MVector3f BasicItem::getPosition(){

	//return position of object
	return m_vPosition;
}
