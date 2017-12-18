#include "GameObject.h"



//	############	//
//	Constructors	//
//	############	//

GameObject::GameObject()
{
	radius = 1;
	bound = 2;
	pos = Vector2(0, 0);
	vel = Vector2(0, 0);
	m = 1;
	force = Vector2(0, 0);
	force_old = Vector2(0, 0);
	pos_old = Vector2(0, 0);
	vel_old = Vector2(0, 0);
}

GameObject::GameObject(double r)
{
	radius = r;
	bound = r + 1;
	pos = Vector2(0, 0);
	vel = Vector2(0, 0);
	m = 1;
	force = Vector2(0, 0);
	force_old = Vector2(0, 0);
	pos_old = Vector2(0, 0);
	vel_old = Vector2(0, 0);
}

GameObject::GameObject(double r, double b)
{
	radius = r;
	bound = b;
	pos = Vector2(0, 0);
	vel = Vector2(0, 0);
	m = 1;
	force = Vector2(0, 0);
	force_old = Vector2(0, 0);
	pos_old = Vector2(0, 0);
	vel_old = Vector2(0, 0);
}

GameObject::GameObject(double r, double b, Vector2 position, Vector2 velocity)
{
	radius = r;
	bound = b;
	pos = position;
	vel = velocity;
	m = 1;
	force = Vector2(0, 0);
	force_old = Vector2(0, 0);
	pos_old = pos;
	vel_old = vel;
}

GameObject::GameObject(double r, Vector2 position, Vector2 velocity)
{
	radius = r;
	bound = r + 1;
	pos = position;
	vel = velocity;
	m = 1;
	force = Vector2(0, 0);
	force_old = Vector2(0, 0);
	pos_old = pos;
	vel_old = vel;
}

GameObject::GameObject(SpriteSheet ss, double r, Vector2 position, Vector2 velocity)
{
	sprite = ss;
	radius = r;
	bound = r + 1;
	pos = position;
	vel = velocity;
	m = 1;
	force = Vector2(0, 0);
	force_old = Vector2(0, 0);
	pos_old = pos;
	vel_old = vel;
}

//	#########	//
//	Functions	//
//	#########	//

void GameObject::setMass(double mass)
{
	m = mass;
}

void GameObject::setSprite(SpriteSheet ss)
{
	sprite = ss;
}

//Converts contents of GameObject to a string
std::string GameObject::toString()
{
	std::stringstream sstream;
	sstream << "Radius: " << radius << "\nPosition: " << pos.toString() << "\nVelocity: " << vel.toString();
	return sstream.str();
}