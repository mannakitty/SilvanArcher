#include "main.h"
#include "MCamera.h"




MCamera::MCamera()
{
	MVector3f vZero = MVector3f(0.0f, 0.0f, 0.0f);		// Init a vector to 0 0 0 for our position
	MVector3f vView = MVector3f(0.0f, 1.0f, 0.5f);		// Init a starting view vector (looking up and out the screen) 
	MVector3f vUp   = MVector3f(0.0f, 0.0f, 1.0f);		// Init a standard up vector (Rarely ever changes)

	m_vPosition	= vZero;					// Init the position to zero
	m_vView		= vView;					// Init the view to a std starting view
	m_vUpVector	= vUp;						// Init the UpVector

	m_speed = MVector3f(5.0f, 0.0f, 5.0f);

	
}

void MCamera::PositionCamera(float positionX, float positionY, float positionZ,
				  		     float viewX,     float viewY,     float viewZ,
							 float upVectorX, float upVectorY, float upVectorZ)
{
	MVector3f vPosition	= MVector3f(positionX, positionY, positionZ);
	MVector3f vView		= MVector3f(viewX, viewY, viewZ);
	MVector3f vUpVector	= MVector3f(upVectorX, upVectorY, upVectorZ);

	// The code above just makes it cleaner to set the variables.
	// Otherwise we would have to set each variable x y and z.

	m_vPosition = vPosition;					// Assign the position
	m_vView     = vView;						// Assign the view
	m_vUpVector = vUpVector;					// Assign the up vector
	
	MVector3f minPoint(1.0f, 2.0f, 1.0f);
	minPoint = m_vPosition - minPoint;

	MVector3f maxPoint(1.0f, 2.0f, 1.0f);
	maxPoint = m_vPosition + maxPoint;
	
	bBox.Set(minPoint, maxPoint);
}

void MCamera::SetViewByMouse(float dt)
{
	POINT mousePos;									// This is a window structure that holds an X and Y
	int middleX = SCREEN_WIDTH  >> 1;				// This is a binary shift to get half the width
	int middleY = SCREEN_HEIGHT >> 1;				// This is a binary shift to get half the height
	float angleY = 0.0f;							// This is the direction for looking up or down
	float angleZ = 0.0f;							// This will be the value we need to rotate around the Y axis (Left and Right)
	static float currentRotX = 0.0f;
	
	// Get the mouse's current X,Y position
	GetCursorPos(&mousePos);						
	
	// If our cursor is still in the middle, we never moved... so don't update the screen
	if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;

	// Set the mouse position to the middle of our window
	SetCursorPos(middleX, middleY);							

	// Get the direction the mouse moved in, but base on dt so rotation is consistent between different computers
	angleY = (float)( (middleX - mousePos.x) ) / 500.0f;		
	angleZ = (float)( (middleY - mousePos.y) ) / 500.0f;		

	// Here we keep track of the current rotation (for up and down) so that
	// we can restrict the camera from doing a full 360 loop.
	currentRotX -= angleZ;  

	// If the current rotation (in radians) is greater than 1.0, we want to cap it.
	if(currentRotX > 1.0f)
		currentRotX = 1.0f;
	// Check if the rotation is below -1.0, if so we want to make sure it doesn't continue
	else if(currentRotX < -1.0f)
		currentRotX = -1.0f;
	// Otherwise, we can rotate the view around our position
	else
	{
		// To find the axis we need to rotate around for up and down
		// movements, we need to get a perpendicular vector from the
		// camera's view vector and up vector.  This will be the axis.
		MVector3f vAxis = (m_vView - m_vPosition) % m_vUpVector;
		vAxis.Normalize();

		// Rotate around our perpendicular axis and along the y-axis
		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	// Rotate around the y axis no matter what the currentRotX is
	RotateView(angleY, 0, 1, 0);
}

void MCamera::RotateView(float angle, float x, float y, float z)
{
	MVector3f vNewView;

	// Get the view vector (The direction we are facing)
	MVector3f vView = m_vView - m_vPosition;		

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

	// Find the new y position for the new rotated point
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

	// Find the new z position for the new rotated point
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	m_vView = m_vPosition + vNewView;
}

void MCamera::StrafeCamera(MVector3f speed, MHeightMapTerrain &g)
{	
		// Add the strafe vector to our position
	m_vPosition.x += m_vStrafe.x * speed.x;
		m_vPosition.z += m_vStrafe.z * speed.x;
	
		float yHight = g.ReturnGroundHeight(m_vPosition);	// find the terrain hight from the heightmap for the current position
		m_vPosition.y = yHight + 2;							// and make the position equal to the above plus 2

		// Add the strafe vector to our view
		m_vView.x += m_vStrafe.x * speed.x;
		m_vView.z += m_vStrafe.z * speed.y;

		//to create a bounding around player/camera position
		MVector3f minPoint(1.0f, 2.0f, 1.0f);
		minPoint = m_vPosition - minPoint;

		MVector3f maxPoint(1.0f, 2.0f, 1.0f);
		maxPoint = m_vPosition + maxPoint;
	
		bBox.Set(minPoint, maxPoint);
}

void MCamera::MoveCamera(MVector3f speed, MHeightMapTerrain &g)
{
		// Get the current view vector (the direction we are looking)
		MVector3f vVector = m_vView - m_vPosition;
		vVector.Normalize();

		m_vPosition.x += (vVector.x * speed.x);		// Add our acceleration to our position's X
		m_vPosition.z += (vVector.z * speed.z);		// Add our acceleration to our position's Z
	
		float yHight = g.ReturnGroundHeight(m_vPosition);	// find the terrain hight from the heightmap for the current position
		m_vPosition.y = (yHight + 2);						// and make the position equal to the above plus 2

		m_vView.x += vVector.x * speed.x;			// Add our acceleration to our view's X
		m_vView.z += vVector.z * speed.z;			// Add our acceleration to our view's Z

		//to create a bounding around player/camera position
		MVector3f minPoint(1.0f, 2.0f, 1.0f);
		minPoint = m_vPosition - minPoint;

		MVector3f maxPoint(1.0f, 2.0f, 1.0f);
		maxPoint = m_vPosition + maxPoint;
	
		bBox.Set(minPoint, maxPoint);
	
}

void MCamera::Update(float dt, bool n) 
{
	//if camera jitter is true add random amoubt to x and z
	if(n == true){	
		MVector3f m;
		int r = rand()%10;
		if(r < 5){
			m.x = (float)((rand() % 100));
			m.x = m.x/1000;
		}
		else{
			m.x = -(float)((rand() % 100));
			m.x = m.x/1000;
		}
		m.y = 0;
		r = rand()%10;
		if(r < 5){
			m.z = (float)((rand() % 100));
			m.z = m.z/1000;
		}
		else{
			m.z = -(float)((rand() % 100));
			m.z = m.z/1000;
		}
		
		
		// update position
		m_vPosition = m_vPosition + m;
		
		// update bounding box
		MVector3f minPoint(1.0f, 2.0f, 1.0f);
		minPoint = m_vPosition - minPoint;

		MVector3f maxPoint(1.0f, 2.0f, 1.0f);
		maxPoint = m_vPosition + maxPoint;
	
		bBox.Set(minPoint, maxPoint);
		// Initialize a variable for the cross product result
		m_vStrafe = (m_vView - m_vPosition) % m_vUpVector;

		// Normalize the strafe vector
		m_vStrafe.Normalize();

		// Move the camera's view by the mouse
		SetViewByMouse(dt);
	}
	else{
		// Initialize a variable for the cross product result
		m_vStrafe = (m_vView - m_vPosition) % m_vUpVector;

		// Normalize the strafe vector
		m_vStrafe.Normalize();

		// Move the camera's view by the mouse
		SetViewByMouse(dt);
	}
	

}

void MCamera::Look()
{
	// Give openGL our camera position, then camera view, then camera up vector
	gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,	
			  m_vView.x,	 m_vView.y,     m_vView.z,	
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}

MVector3f MCamera::GetPosition()
{
	return m_vPosition;
}


float MCamera::getYView(){
	return m_vView.y;
}

MVector3f MCamera::getSpeed(){
	return m_speed;
}

void MCamera::setYPosition(float y){
	m_vPosition.y = y;
}

void MCamera::setYView(float y){
	m_vView.y = y;
}

MBoundingBox MCamera::getBBox(){
	return bBox;
}

void MCamera::setPosition(MVector3f newPosition){
	m_vPosition += newPosition;
}