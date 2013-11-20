#include "MaterialEffects.h"


void MaterialEffects::SetDefaultMaterial()
{
	// enable and set color material to help with shading
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Set values for material properties to help with shading
	GLfloat ambientMaterial[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuseMaterial[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat specularMaterial[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat emissionMaterial[] = {0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
}