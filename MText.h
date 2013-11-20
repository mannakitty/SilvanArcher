#pragma once

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include ".\include\glut.h"	

class MText
{
public:
	MText();
	~MText();
	void Render(char text[20], float x, float y, void *font);

private:
	void SetOrthographicProjection();
	void ResetPerspectiveProjection();
	void RenderBitmapString(float x, float y, void *font,char *string);
};

