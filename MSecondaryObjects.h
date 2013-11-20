#include "MModel_3DS.h"
#include ".\include\glut.h"	
#include "MVector3f.h"


class MSecondaryObjects
{
public:

	void Load();  //Method to load the secondary models
	void Render(MVector3f cowPosition, MVector3f treePosition);  //Method to render the secondary models

private:
	MModel_3DS m_cowModel;  //Cow Model
	MModel_3DS m_treeModel; //tree model
};



