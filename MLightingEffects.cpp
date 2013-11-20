#include "MLightingEffects.h"	



void MLightingEffects::SetDefaultLighting(MHeightMapTerrain &g_heightMapTerrain)
{
	
	//Enable lighting
	glEnable(GL_LIGHTING);
	//Enable a light
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	//Enable normals
	glEnable(GL_NORMALIZE);
	
	//Define the ambient light intensity
	GLfloat ambientIntensity[] = {0.2f, 0.2f, 0.2f, 0.5f};
	//Set ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntensity);
	
	// Set shade model
	glShadeModel(GL_SMOOTH);
	
	//Add directed light which will act as sun direction
	//Set light color
    GLfloat diffuseLight0[] = {0.5f, 0.5f, 0.5f, 0.5f}; 
	GLfloat ambientLight0[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat specularLight0[] = {1.0, 1.0, 1.0, 0.5};
    //Set light position
	GLfloat lightPos0[] = {100.0f, 15.0f, 0.0f, 0.0f};

	// Add orange light for camp fire
	GLfloat diffuseLight1[] = {1.0, 0.5, 0.0, 0.5};
	GLfloat ambientLight1[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat specularLight1[] = {1.0, 0.5, 0.0, 0.5};
	MVector3f temp1 = MVector3f(40.0, 0.0, 60.0);
	float y1 = g_heightMapTerrain.ReturnGroundHeight(temp1);
	GLfloat lightPos1[] = {40, y1, 60, 1.0};

	// Add  lights for spotlight path
	GLfloat diffuseLight2[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat ambientLight2[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat specularLight2[] = {1.0, 1.0, 1.0, 1.0};
	MVector3f temp2 = MVector3f(10.0, 0.0, -60.0);
 	float y2 = g_heightMapTerrain.ReturnGroundHeight(temp2) + 5;
	GLfloat lightPos2[] = {10, y2, -60, 1.0};
	GLfloat lightDir2[] = {0.750f, -0.550f, -1.0f};

	GLfloat diffuseLight3[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat ambientLight3[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat specularLight3[] = {1.0, 1.0, 1.0, 1.0};
	MVector3f temp3 = MVector3f(10.0, 0.0, -75.0);
 	float y3 = g_heightMapTerrain.ReturnGroundHeight(temp3) + 5;
	GLfloat lightPos3[] = {10, y3, -75, 1.0};
	GLfloat lightDir3[] = {0.750f, -0.55f, 1.0f};

	GLfloat diffuseLight4[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat ambientLight4[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat specularLight4[] = {1.0, 1.0, 1.0, 1.0};
	MVector3f temp4 = MVector3f(25.0, 0.0, -60.0);
 	float y4 = g_heightMapTerrain.ReturnGroundHeight(temp4) + 5;
	GLfloat lightPos4[] = {25, y4, -60, 1.0};
	GLfloat lightDir4[] = {0.750f, -0.55f, -1.0f};

	GLfloat diffuseLight5[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat ambientLight5[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat specularLight5[] = {1.0, 1.0, 1.0, 1.0};
	MVector3f temp5 = MVector3f(25.0, 0.0, -75.0);
 	float y5 = g_heightMapTerrain.ReturnGroundHeight(temp5) + 5;
	GLfloat lightPos5[] = {25, y5, -75, 1.0};
	GLfloat lightDir5[] = {0.750f, -0.55f, 1.0f};

	// Create lights
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glPopMatrix();

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glPopMatrix();

	glPushMatrix();
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0f);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight3);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightDir3);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 15.0f);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseLight4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientLight4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specularLight4);
	glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightDir4);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 15.0f);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuseLight5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, ambientLight5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, specularLight5);
	glLightfv(GL_LIGHT5, GL_POSITION, lightPos5);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, lightDir5);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 15.0f);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 2.0f);
	glPopMatrix();

	//Add attenuation for campfire light
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001);

	// Add attenuation for spotlight lights
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.001);

	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.001);

	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.001);

	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.001);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.001);
}