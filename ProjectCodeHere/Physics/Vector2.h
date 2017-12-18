#pragma once

#include <cmath>
#include <string>
#include <sstream>

class Vector2
{
	public:
		double x, y;

		// Constructors
		Vector2();
		Vector2(double X, double Y);
		~Vector2();

		// Operators
		Vector2 operator+ (const Vector2 rhs);
		Vector2 operator+ (const double rhs);
		Vector2 operator- (const Vector2 rhs);
		Vector2 operator- (const double rhs);
		double operator* (const Vector2 rhs);
		Vector2 operator* (const double rhs);
		Vector2 operator/ (const double rhs);
		bool operator== (const Vector2 rhs);
		bool operator!= (const Vector2 rhs);

		// Functions
		double mag();
		double mag2();
		Vector2 norm();
		Vector2 reflect(const Vector2 vec);
		std::string toString();
};