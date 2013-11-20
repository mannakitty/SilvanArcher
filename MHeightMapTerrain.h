#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library
#include <vector>
#include "MVector3f.h"
#include "MFaceVertexMesh.h"


class MHeightMapTerrain
{
public:
	MHeightMapTerrain();
	~MHeightMapTerrain();
	bool GenerateFromBMP(char *filename, MVector3f origin, float terrainSizeX, float terrainSizeZ, float terrainHeightScale);
	float ReturnGroundHeight(MVector3f p);
	void Render(MVector3f origin, MVector3f size);

private:
	int m_width, m_height;
	float *m_heightMap;
	MFaceVertexMesh m_mesh;
	UINT m_hTexture;
	float m_terrainSizeX, m_terrainSizeZ;
	MVector3f m_origin;


	MVector3f WorldToImageCoordinates(MVector3f p);
	MVector3f ImageToWorldCoordinates(MVector3f p);
};