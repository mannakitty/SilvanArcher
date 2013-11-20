#pragma once
#include "Math.h"

// Vector class, written by Greg Slabaugh (gregory.slabaugh.1@city.ac.uk)
// Version 1.0, 13 Jan 2012


class MVector3f
{
public:
	// Constructors
	MVector3f(){};
	MVector3f(float xIn, float yIn, float zIn) {
		x = xIn;
		y = yIn;
		z = zIn;
	}
	MVector3f(int xIn, int yIn, int zIn) {
		x = (float) xIn;
		y = (float) yIn;
		z = (float) zIn;
	}
	MVector3f(double xIn, double yIn, double zIn) {
		x = (float) xIn;
		y = (float) yIn;
		z = (float) zIn;
	}
	MVector3f(const MVector3f& p) {*this = p;}

	// Destructors
	virtual ~MVector3f(){};
	
	// Vector addition and subtraction (operator overloading)
	MVector3f operator +(const MVector3f& p) const {return MVector3f(x+p.x, y+p.y, z+p.z);}
	MVector3f operator -(const MVector3f& p) const {return MVector3f(x-p.x, y-p.y, z-p.z);}
	MVector3f& operator +=(const MVector3f& p) {*this = *this + p; return *this;}
	MVector3f& operator -=(const MVector3f& p) {*this = *this - p; return *this;}
 
	// Post-multiple or divide by a scalar (operator overloading)
	MVector3f operator *(const float s) const {return MVector3f(x*s, y*s, z*s);}
	MVector3f operator /(const float s) const {return MVector3f(x/s, y/s, z/s);}
	MVector3f& operator *=(const float s) {*this = *this * s; return *this;} 
	MVector3f& operator /=(const float s) {*this = *this / s; return *this;}

	// Pre-multiply or divide by a scalar (operator overloading)
	friend MVector3f operator *(const float s, const MVector3f& p) {return p * s;}
	friend MVector3f operator /(const float s, const MVector3f& p) {return p / s;}

	// Equality and inequality (operator overloading)
	bool operator==(const MVector3f& other) const { return ( x == other.x && y == other.y && z == other.z ); }
	bool operator!=(const MVector3f& other) const { return ( x != other.x || y != other.y || z != other.z ); }
 
	// Dot product (operator overloading)
	float operator *(const MVector3f& p) const {return x*p.x + y*p.y + z*p.z;}
	
	// Cross product (operator overloading)
	MVector3f operator %(const MVector3f& p) const {return MVector3f(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x);}
	MVector3f& operator %=(const MVector3f& p) {*this = *this % p; return *this;}

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

