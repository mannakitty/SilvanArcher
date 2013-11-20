#include "MHeightMapTerrain.h"
#include "MLightingEffects.h"
#include "include\glut.h"
#include "include\glaux.h"
#include "MTexture.h"


MHeightMapTerrain::MHeightMapTerrain()
{}

MHeightMapTerrain::~MHeightMapTerrain()
{
	delete [] m_heightMap;
}

// Convert a point from image (pixel) coordinates to world coordinates
MVector3f MHeightMapTerrain::ImageToWorldCoordinates(MVector3f p)
{
	// Normalize the image point so that it in the range [-1, 1] in x and [-1, 1] in z
	p.x = 2.0f * (p.x / m_width) - 1.0f;
	p.z = 2.0f * (p.z / m_height) - 1.0f;

	// Now scale the point so that the terrain has the right size in x and z
	p.x *= m_terrainSizeX / 2.0f;
	p.z *= m_terrainSizeZ / 2.0f;

	// Now translate the point based on the origin passed into the function
	p += m_origin;

	return p;

}

// Convert a point from world coordinates to image (pixel) coordinates
MVector3f MHeightMapTerrain::WorldToImageCoordinates(MVector3f p)
{
	p -= m_origin;

	// Normalize the image point so that it in the range [-1, 1] in x and [-1, 1] in z
	p.x *= 2.0f / m_terrainSizeX;
	p.z *= 2.0f / m_terrainSizeZ;

	// Now transform the point so that it is in the range [0, 1] in x and [0, 1] in z
	p.x = (p.x + 1.0f) * (m_width / 2.0f);
	p.z = (p.z + 1.0f) * (m_height / 2.0f);

	return p;

}

// This function generates a heightmap terrain based on a bitmap
bool MHeightMapTerrain::GenerateFromBMP(char *filename, MVector3f origin, float terrainSizeX, float terrainSizeZ, float terrainHeightScale)
{

	// Load bmp
	AUX_RGBImageRec *pBitmap = NULL;
	FILE *pFile = NULL;									// The File Handle we will use to read the bitmap

	fopen_s(&pFile, filename, "r");						// Check To See If The File Exists
	if(pFile)											// If we have a valid file pointer we found the file
			pBitmap = auxDIBImageLoad(filename);			// Load the bitmap and store the data
	else {											// If we can't find the file, quit!
		MessageBox(NULL, "Couldn't find an image texture!", "Error!", MB_OK);
		exit(0);
	}

	m_width = pBitmap->sizeX;
	m_height = pBitmap->sizeY;
	m_origin = origin;
	m_terrainSizeX = terrainSizeX;
	m_terrainSizeZ = terrainSizeZ;
	
	// Allocate memory and initialize to store the image
	m_heightMap = new float[m_width * m_height];
	if (m_heightMap == NULL) 
		return false;

	// Clear the heightmap
	memset(m_heightMap, 0, m_width * m_height * sizeof(float));

	// Form mesh
	std::vector<MVertex> vertices;
	std::vector<unsigned int> triangles;
	float halfSizeX = m_width / 2.0f;
	float halfSizeY = m_height / 2.0f;
	
	int X = 1;
	int Z = m_width;
	int triangleId = 0;
	for (int z = 0; z < m_height; z++) {
		for (int x = 0; x < m_width; x++) {
			int index = x + z * m_width;

			// Retreive the colour from the terrain image, and set the normalized height in the range [0, 1]
			float grayScale = (pBitmap->data[index*3] + pBitmap->data[index*3+1] + pBitmap->data[index*3+2]) / 3.0f;
			float height = (grayScale - 128.0f) / 128.0f;

			// Make a point based on this pixel position.  Then, transform so that the mesh has the correct size and origin
			// This transforms a point in image coordinates to world coordinates
			MVector3f pImage = MVector3f((float) x, height, (float) z);
			MVector3f pWorld = ImageToWorldCoordinates(pImage);

			// Scale the terrain and store for later
			pWorld.y *= terrainHeightScale;	 
			m_heightMap[index] = pWorld.y;

			// Store the point in a vector
			MVertex v = MVertex(pWorld.x, pWorld.y, pWorld.z, 0.0, 0.0, 0.0, 0.0, 0.0);
			vertices.push_back(v);
		}
	}

	// Form triangles from successive rows of the image
	for (int z = 0; z < m_height-1; z++) {
		for (int x = 0; x < m_width-1; x++) {
			int index = x + z * m_width;
			triangles.push_back(index);
			triangles.push_back(index+X+Z);
			triangles.push_back(index+X);

			triangles.push_back(index);
			triangles.push_back(index+Z);
			triangles.push_back(index+X+Z);
		}
	}

	// Create a face vertex mesh
	m_mesh.CreateFromTriangleList(vertices, triangles);

	// Load a texture for texture mapping the mesh
	MTexture texture;
	texture.CreateFromBMP(&m_hTexture, "Resources/Textures/GrassDark.bmp"); 

	// Free memory of the image that was loaded
	if (pBitmap)										// If we loaded the bitmap
	{
		if (pBitmap->data)								// If there is texture data
			free(pBitmap->data);						// Free the bitmap data, we don't need it anymore
		free(pBitmap);									// Free the bitmap structure
	}


	return true;
}

// For a point p in world coordinates, return the height of the terrain
float MHeightMapTerrain::ReturnGroundHeight(MVector3f p)
{
	// Undo the transformation going from image coordinates to world coordinates
	MVector3f pImage = WorldToImageCoordinates(p);
	
	// Bilinear interpolation.
	int xl = (int) floor(pImage.x);
	int zl = (int) floor (pImage.z);
	
	// Check if the position is in the region of the heightmap
	if (xl < 0 || xl >= m_width - 1 || zl < 0 || zl >= m_height -1)
		return 0.0f;
	
	// Get the indices of four pixels around the current point
	int indexll = xl + zl * m_width;
	int indexlr = (xl+1) + zl * m_width;
	int indexul = xl + (zl+1) * m_width;
	int indexur = (xl+1) + (zl+1) * m_width;
	
	// Interpolation amounts in x and z
	float dx = pImage.x - xl;
	float dz = pImage.z - zl;
	
	// Interpolate -- first in x and and then in z
	float a = (1-dx) * m_heightMap[indexll] + dx * m_heightMap[indexlr];
	float b = (1-dx) * m_heightMap[indexul] + dx * m_heightMap[indexur];
	float c = (1-dz) * a + dz * b;
	return c;
}

void MHeightMapTerrain::Render(MVector3f origin, MVector3f size)
{
	glBindTexture(GL_TEXTURE_2D, m_hTexture);
	m_mesh.Render();
}