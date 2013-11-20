#pragma once
#include "MBoundingBox.h"
#include "float.h"


MBoundingBox::MBoundingBox()
{
	m_isValid = false;
	m_xmin = FLT_MAX;
	m_ymin = FLT_MAX;
	m_zmin = FLT_MAX;
	m_xmax = -FLT_MAX;
	m_ymax = -FLT_MAX;
	m_zmax = -FLT_MAX;

}

MBoundingBox::~MBoundingBox()
{}

bool MBoundingBox::FitToMesh(const MModel_3DS *pMesh)
{
	for (int k = 0; k < pMesh->numObjects; k++)
	{
		for (int m = 0; m < pMesh->Objects[k].numVerts; m++)
		{
			float x = pMesh->Objects[k].Vertexes[3*m];
			float y = pMesh->Objects[k].Vertexes[3*m+1];
			float z = pMesh->Objects[k].Vertexes[3*m+2];
			if (x < m_xmin)
				m_xmin = x;
			if (y < m_ymin)
				m_ymin = y;
			if (z < m_zmin)
				m_zmin = z;
			if (x > m_xmax)
				m_xmax = x;
			if (y > m_ymax)
				m_ymax = y;
			if (z > m_zmax)
				m_zmax = z;
		}
	}
	m_isValid = true;
	return true;
}

bool MBoundingBox::GetSizeAndCentre(float &dx, float &dy, float &dz, MVector3f &centre)
{
	if (m_isValid == false)
		return false;

	dx = m_xmax - m_xmin;
	dy = m_ymax - m_ymin;
	dz = m_zmax - m_zmin;
	centre.x = m_xmin + dx / 2.0f;
	centre.y = m_ymin + dy / 2.0f;
	centre.z = m_zmin + dz / 2.0f;

	return true;

}


void MBoundingBox::Render(float r, float g, float b)
{
	
	if (m_isValid == false)
		return;

	glColor3f(r, g, b);
	glBegin(GL_LINE_LOOP);
	glVertex3f(m_xmin, m_ymin, m_zmin);
	glVertex3f(m_xmax, m_ymin, m_zmin);
	glVertex3f(m_xmax, m_ymax, m_zmin);
	glVertex3f(m_xmin, m_ymax, m_zmin);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(m_xmin, m_ymin, m_zmax);
	glVertex3f(m_xmax, m_ymin, m_zmax);
	glVertex3f(m_xmax, m_ymax, m_zmax);
	glVertex3f(m_xmin, m_ymax, m_zmax);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(m_xmin, m_ymin, m_zmin);
	glVertex3f(m_xmin, m_ymin, m_zmax);
	glVertex3f(m_xmax, m_ymin, m_zmin);
	glVertex3f(m_xmax, m_ymin, m_zmax);
	glVertex3f(m_xmax, m_ymax, m_zmin);
	glVertex3f(m_xmax, m_ymax, m_zmax);
	glVertex3f(m_xmin, m_ymax, m_zmin);
	glVertex3f(m_xmin, m_ymax, m_zmax);
	glEnd();

}

void MBoundingBox::Set(MVector3f minPoint, MVector3f maxPoint)
{
	m_isValid = true;
	m_xmin = minPoint.x;
	m_ymin = minPoint.y;
	m_zmin = minPoint.z;
	m_xmax = maxPoint.x;
	m_ymax = maxPoint.y;
	m_zmax = maxPoint.z;

}


void MBoundingBox::Translate(MVector3f t)
{
	m_isValid = true;
	m_xmin += t.x;
	m_ymin += t.y;
	m_zmin += t.z;
	m_xmax += t.x;
	m_ymax += t.y;
	m_zmax += t.z;

}

//set in regards to height map
void MBoundingBox::TranslateY(float yMovement)
{
	m_ymin += yMovement;
	m_ymax += yMovement;
}

//still in testing, rotating bounding box to stay around mesh
void MBoundingBox::rotate(float angle){


	angle = ((angle)) / -180;

	float s = sin(angle);
	float c = cos(angle);

	m_xmax -=  m_xmin;
	m_zmax -=  m_zmin;

	float xnew = m_xmax * c + m_zmax * s;
	float znew = -m_xmax * s + m_zmax * c;

	m_xmax = (xnew + m_xmin) + 1;
	m_zmax = (znew + m_zmin) + 1;
	
	//m_xmax = (cos(angle) * (m_xmax - m_xmin) - sin(angle) * (m_xmax + m_xmin));
	//m_zmax = (sin(angle) * (m_zmax + m_zmin) - cos(angle) * (m_zmax + m_zmin));
}

//return current max point
MVector3f MBoundingBox::returnMaxPoint(){

	return MVector3f(m_xmax,m_ymax,m_zmax);

}

//return current min point
MVector3f MBoundingBox::returnMinPoint(){

	return MVector3f(m_xmin,m_ymin,m_zmin);

}
