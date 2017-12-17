#pragma once

#include "Vector2.h"
#include "Sprite.h"
#include "SpriteSheet.h"

class GameObject
{
	public:
		//	Variables
		SpriteSheet sprite;		//	Sprite of the object
		double radius;			//	Radius of the object
		double bound;			//	Radius of the bounding circle; used for collision detection
		Vector2 pos;			//	Vector representing the position of the object
		Vector2 vel;			//	Vector representing the velocity of the object
		double m;				//	Mass of the object
		Vector2 force;
		Vector2 force_old;
		Vector2 pos_old;
		Vector2 vel_old;

		//	Constructors
		GameObject();
		GameObject(double r);
		GameObject(double r, double bs);
		GameObject(double r, double bs, Vector2 position, Vector2 velocity);
		GameObject(double r, Vector2 position, Vector2 velocity);
		GameObject(SpriteSheet ss, double r, Vector2 position, Vector2 velocity);

		//	Functions
		void setMass(double mass);
		void setSprite(SpriteSheet ss);
		std::string toString();
};