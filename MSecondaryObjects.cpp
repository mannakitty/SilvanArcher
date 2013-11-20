#include "MSecondaryObjects.h"
#include "MBoundingBox.h"


void MSecondaryObjects::Load()
{
	m_cowModel.Load("./Resources/3DS/cow2.3ds"); // Load a 3ds model
	m_treeModel.Load("Resources/3DS/elm.3ds");
}

void MSecondaryObjects::Render(MVector3f cowPosition, MVector3f treePosition)
{
	/*
	MBoundingBox bbox;
	float dx, dy, dz;
	MVector3f centre;
	bbox.FitToMesh(&m_cowModel);
	bbox.GetSizeAndCentre(dx, dy, dz, centre);
	*/

	//m_cowModel.scale = 1.3f / dy;//Scale the model so tha it is 1.3 meters
	m_cowModel.scale = 0.204f;//Scale the model so tha it is 1.3 meters
	m_cowModel.pos.x = cowPosition.x;//Set the x position
	m_cowModel.pos.y = cowPosition.y;//Set the y position
	m_cowModel.pos.z = cowPosition.z;//Set the z position
	m_cowModel.rot.x = 0.0f;//Set the rotation about the x axis
	m_cowModel.rot.y = 0.0f;//Set the rotation about the y axis
	m_cowModel.rot.z = 0.0f;//Set the rotation about the z axis
	m_cowModel.Draw(); //Draw cow model

	/*
	bbox.FitToMesh(&m_treeModel);
	bbox.GetSizeAndCentre(dx, dy, dz, centre);
	*/

	//m_treeModel.scale = 15.0f / dy;//Scale the model so that it is 15 meters
	m_treeModel.scale = 0.034f;//Scale the model so that it is 15 meters
	m_treeModel.pos.x = treePosition.x;//Set the x position
	m_treeModel.pos.y = treePosition.y;//Set the y position
	m_treeModel.pos.z = treePosition.z;//Set the z position
	m_treeModel.rot.x = 0.0f;//Set the rotation about the x axis
	m_treeModel.rot.y = 0.0f;//Set the rotation about the y axis
	m_treeModel.rot.z = 0.0f;//Set the rotation about the z axis
	m_treeModel.Draw(); //Draw tree model
};