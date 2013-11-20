#pragma once
#include "Math.h"

class Vertex3f
{
public:
	// Constructors
	Vertex3f(){};
	Vertex3f(float xIn, float yIn, float zIn) {
		x = xIn;
		y = yIn;
		z = zIn;
	}
	Vertex3f(int xIn, int yIn, int zIn) {
		x = (float) xIn;
		y = (float) yIn;
		z = (float) zIn;
	}
	Vertex3f(const Vertex3f& p) {*this = p;}

	// Destructors
	virtual ~Vertex3f(){};
	
	// Vector addition and subtraction
	Vertex3f operator +(const Vertex3f& p) const {return Vertex3f(x+p.x, y+p.y, z+p.z);}
	Vertex3f operator -(const Vertex3f& p) const {return Vertex3f(x-p.x, y-p.y, z-p.z);}
	Vertex3f& operator +=(const Vertex3f& p) {*this = *this + p; return *this;}
	Vertex3f& operator -=(const Vertex3f& p) {*this = *this - p; return *this;}
 
	// Post-multiple or divide by a scalar
	Vertex3f operator *(const float s) const {return Vertex3f(x*s, y*s, z*s);}
	Vertex3f operator /(const float s) const {return Vertex3f(x/s, y/s, z/s);}
	Vertex3f& operator *=(const float s) {*this = *this * s; return *this;} 
	Vertex3f& operator /=(const float s) {*this = *this / s; return *this;}

	// Pre-multiply or divide by a scalar
	friend Vertex3f operator *(const float s, const Vertex3f& p) {return p * s;}
	friend Vertex3f operator /(const float s, const Vertex3f& p) {return p / s;}

	// Equality and inequality
	bool operator==(const Vertex3f& other) const { return ( x == other.x && y == other.y && z == other.z ); }
	bool operator!=(const Vertex3f& other) const { return ( x != other.x || y != other.y || z != other.z ); }
 
	// Dot product
	float operator *(const Vertex3f& p) const {return x*p.x + y*p.y + z*p.z;}
	
	// Cross product
	Vertex3f operator %(const Vertex3f& p) const {return Vertex3f(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x);}
	Vertex3f& operator %=(const Vertex3f& p) {*this = *this % p; return *this;}

	/*
	// Matrix multiplication (left multiply)
	MFPoint operator *(const Matrix3x3 &m) const 
	{
		MFPoint result;

		result.x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z;
		result.y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z;
		result.z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z;

		return result;
	}
	// Matrix multiplication (right multiply)
	friend MFPoint operator *(const Matrix3x3 &m, const MFPoint& p) {
		MFPoint result;
		result.x = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2] * p.z;
		result.y = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2] * p.z;
		result.z = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2] * p.z;
		return result;
	}

	// Matrix multiplication (right multiply)
	friend MFPoint operator *(const MatrixNxM &m, const MFPoint& p) {
		MFPoint result;
		result.x = m.m[1][1] * p.x + m.m[1][2] * p.y + m.m[1][3] * p.z;
		result.y = m.m[2][1] * p.x + m.m[2][2] * p.y + m.m[2][3] * p.z;
		result.z = m.m[3][2] * p.x + m.m[3][2] * p.y + m.m[3][3] * p.z;
		return result;
	}

	// Matrix multiplication
	MFPoint operator *(const Matrix3x4 &m) const 
	{
		MFPoint result;

		result.x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		result.y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		result.z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];

		return result;
	}
*/

	// Length, normalisation
	float Length() {
		return sqrtf(*this * *this);
	}
	void Normalize() {
		*this = *this / Length();
	}

	float x;
	float y;
	float z;
};

