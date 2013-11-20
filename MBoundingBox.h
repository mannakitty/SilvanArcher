#pragma once
#include "MVector3f.h"
#include "MModel_3DS.h"

class MBoundingBox
{
public:
	MBoundingBox();
	~MBoundingBox();
	bool FitToMesh(const MModel_3DS *pMesh);
	bool GetSizeAndCentre(float &dx, float &dy, float &dz, MVector3f &centre);
	void Render(float r, float g, float b);
	void Set(MVector3f minPoint, MVector3f maxPoint);
	void Translate(MVector3f t);
	void TranslateY(float yMovement);
	void rotate(float angle);
	MVector3f returnMinPoint();
	MVector3f returnMaxPoint();
	//MVector3f operator set(const MVector3f& other) const { return ( m_xmax == other.x && m_ymax == other.y && m_zmax == other.z ); }
private:
	bool m_isValid;
	float m_xmin;
	float m_ymin;
	float m_zmin;
	float m_xmax;
	float m_ymax;
	float m_zmax;

};


