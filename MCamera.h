#ifndef _CAMERA_H
#define _CAMERA_H

#include "MVector3f.h"
#include "MHeightMapTerrain.h"
#include "MBoundingBox.h"

// This is the camera class
class MCamera {

public:

	// This is the camera constructor
	MCamera();	

	MVector3f Position() {	return m_vPosition;		} //Get Camera Position
	MVector3f View()		{	return m_vView;			} //Get Camera View
	MVector3f UpVector() {	return m_vUpVector;		} //
	MVector3f Strafe()	{	return m_vStrafe;		} //
	
	// This changes the position, view, and up vector of the camera.
	// This is primarily used for initialization
	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);

	// This rotates the camera's view around the position depending on the values passed in.
	void RotateView(float angle, float X, float Y, float Z);

	// This moves the camera's view by the mouse movements (First person view)
	void SetViewByMouse(float dt); 

	// This rotates the camera around a point (I.E. your character).
	void RotateAroundPoint(MVector3f vCenter, float X, float Y, float Z);

	// This strafes the camera left or right depending on the speed (+/-) 
	void StrafeCamera(MVector3f speed, MHeightMapTerrain &g);

	// This will move the camera forward or backward depending on the speed
	void MoveCamera(MVector3f speed, MHeightMapTerrain &g);

	// This updates the camera's view and other data (Should be called each frame)
	void Update(float dt, bool n);

	// This uses gluLookAt() to tell OpenGL where to look
	void Look(); 

	
	MVector3f GetPosition();
	MBoundingBox getBBox();
	void setPosition(MVector3f newPosition);


	float getYView();
	MVector3f getSpeed();
	float getFrameInterval();
	void setYPosition(float y);
	void setYView(float y);
	


private:

	// The camera's position
	MVector3f m_vPosition;					

	// The camera's view
	MVector3f m_vView;						

	// The camera's up vector
	MVector3f m_vUpVector;		
	
	// The camera's strafe vector
	MVector3f m_vStrafe;		

	// This is how fast our camera moves
	MVector3f m_speed;

	MBoundingBox bBox;

};

#endif