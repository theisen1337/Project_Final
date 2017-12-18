#include "Vector2.h"

//	############	//
//	Constructors	//
//	############	//
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(double X, double Y)
{
	x = X;
	y = Y;
}

Vector2::~Vector2()
{

}



//	#########	//
//	Operators	//
//	#########	//

//Vector addition
Vector2 Vector2::operator+ (const Vector2 rhs)
{
	return Vector2(x + rhs.x, y + rhs.y);
}

//Scalar addition
Vector2 Vector2::operator+ (const double rhs)
{
	return Vector2(x + rhs, y + rhs);
}

//Vector subtraction
Vector2 Vector2::operator- (const Vector2 rhs)
{
	return Vector2(x - rhs.x, y - rhs.y);
}

//Scalar subtraction
Vector2 Vector2::operator- (const double rhs)
{
	return Vector2(x - rhs, y + rhs);
}

//Scalar multiplication
Vector2 Vector2::operator* (const double rhs)
{
	return Vector2(x * rhs, y * rhs);
}

//Dot product
double Vector2::operator* (const Vector2 rhs)
{
	return (x * rhs.x) + (y * rhs.y);
}

//Scalar division
Vector2 Vector2::operator/ (const double rhs)
{
	return Vector2(x / rhs, y / rhs);
}

bool Vector2::operator== (const Vector2 rhs)
{
	if (x == rhs.x && y == rhs.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vector2::operator!= (const Vector2 rhs)
{
	if (x != rhs.x || y != rhs.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//	#########	//
//	Functions	//
//	#########	//

//Returns scalar representing the magnitude of the vector
double Vector2::mag()
{
	return sqrt((x*x) + (y*y));
}

//Returns scalar representing the squared magnitude of the vector
double Vector2::mag2()
{
	return (x*x) + (y*y);
}

//Returns Vector2 normalized to be between 0 and 1
Vector2 Vector2::norm()
{
	return Vector2(x / mag(), y / mag());
}

//Returns Vector2 that is a reflection of itself
Vector2 Vector2::reflect(Vector2 n)
{
	Vector2 vec = Vector2(x, y);
	return vec - (n * 2* (vec * n));
}

std::string Vector2::toString()
{
	std::stringstream sstream;
	sstream << '(' << x << ", " << y << ')';
	return sstream.str();
}