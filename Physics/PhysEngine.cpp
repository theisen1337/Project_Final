#include <iostream>
#include <cmath>
#include "PhysEngine.h"



//	############	//
//	Constructors	//
//	############	//

PhysEngine::PhysEngine()
{
	gameObjects = std::vector<GameObject>();
	listSize = 0;
	width = 800;
	height = 600;
	gravity = Vector2(0, 0);
	dt = 0.01;
}

PhysEngine::PhysEngine(double deltaTime, int w, int h)
{
	gameObjects = std::vector<GameObject>();
	listSize = 0;
	width = w;
	height = h;
	gravity = Vector2(0, 0);
	dt = deltaTime;
}

PhysEngine::~PhysEngine()
{
}



//	##############	//
//	Physics Engine	//
//	##############	//

//Set the strength and direction of gravity
void PhysEngine::setGravity(Vector2 g)
{
	gravity = g;
}

//Add force to GameObject at index i
void PhysEngine::addForce(int i, Vector2 force)
{
	gameObjects.at(i).force = gameObjects.at(i).force + force;
}

//Net the forces in the force queue
void PhysEngine::netForce(int i)
{
		gameObjects.at(i).force = Vector2(0, 0);
}

//Add a GameObject to the game list
void PhysEngine::addGameObject(GameObject go)
{
	gameObjects.push_back(go);
}

//Remove a GameObject from the game list
void PhysEngine::removeGameObject()
{
	gameObjects.pop_back();
}

//Print list of GameObjects to the console
void PhysEngine::printGameObjects()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		std::cout << "\nGameObject " << i << std::endl << gameObjects.at(i).toString() << std::endl;
	}
}

//Apply force of gravity to object at index i
void PhysEngine::forceGravity(int i)
{
	gameObjects.at(i).force = gameObjects.at(i).force + (gravity * gameObjects.at(i).m);
}

//Applies numerical method of backwards euler to GameObject at index i
void PhysEngine::beuler(int i)
{
	std::cout << "vel_old" << gameObjects.at(i).vel_old.toString() << std::endl;
	gameObjects.at(i).vel = gameObjects.at(i).vel_old + gameObjects.at(i).force_old * dt;
	gameObjects.at(i).pos = gameObjects.at(i).pos_old + gameObjects.at(i).vel * dt;

	gameObjects.at(i).vel_old = gameObjects.at(i).vel;
	gameObjects.at(i).pos_old = gameObjects.at(i).pos;
	gameObjects.at(i).force_old = gameObjects.at(i).force;

	netForce(i);
}

//Applies numerical method of verlet to GameObject at index i
void PhysEngine::verlet(int i)
{
	Vector2 force = gameObjects.at(i).force;
	Vector2 pos_old = gameObjects.at(i).pos_old;
	Vector2 vel_old = gameObjects.at(i).vel_old;
	Vector2 force_old = gameObjects.at(i).force_old;
	double m = gameObjects.at(i).m;
	
	gameObjects.at(i).pos = pos_old + gameObjects.at(i).vel*dt + (force / (2 * m))*pow(dt, 2);
	gameObjects.at(i).vel = vel_old + ((force + force_old) / m)*0.5*dt;

	gameObjects.at(i).pos_old = gameObjects.at(i).pos;
	gameObjects.at(i).vel_old = gameObjects.at(i).vel;
	gameObjects.at(i).force_old = gameObjects.at(i).force;

	netForce(i);
}

void PhysEngine::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		forceGravity(i);
		verlet(i);
		boundary(i);
	}
	broadphase();
}



//	################	//
//	Collision Engine	//
//	################	//

//Broadphase collision detection
void PhysEngine::broadphase()
{
	std::cout << "Inside broadphase" << std::endl;
	int size = gameObjects.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (gameObjects[i].bound + gameObjects[j].bound > (gameObjects[i].pos - gameObjects[j].pos).mag())
			{
				std::cout << "Near collision detected" << std::endl;
				narrowphase(gameObjects[i], gameObjects[j]);
			}
		}
	}
}

//Narrowphase collision detection
void PhysEngine::narrowphase(GameObject &obj1, GameObject &obj2)
{
	//	If circles representing objects intersect, resolve collision
	if ((obj1.radius + obj2.radius) > (obj2.pos - obj1.pos).mag())
	{
		std::cout << "Collision detected" << std::endl;
		collide(obj1, obj2);
	}
}

Vector2 PhysEngine::getCollisionNormal(GameObject &obj1, GameObject &obj2)
{
	return (obj2.pos - obj1.pos).norm();
}

//Resolves collision of two GameObjects
void PhysEngine::collide(GameObject &obj1, GameObject &obj2)
{
	Vector2 normal = getCollisionNormal(obj1, obj2);
	std::cout << "Mag: " << (obj2.pos - obj1.pos).mag() << std::endl;
	std::cout << "Normal: " << normal.toString() << std::endl;

	// Calculate relative velocity
	Vector2 rv = obj2.vel - obj1.vel;

	// Calculate relative velocity in terms of the normal
	double velAlongNormal = rv * normal;
	std::cout << "velAlongNormal: " << velAlongNormal << std::endl;

	// Ignore objects heading away from each other
	if (velAlongNormal > 0) {
		return;
	}

	// Get impulse
	double j = (1 + 0.95) * velAlongNormal;
	j /= ((1 / obj1.m) + (1 / obj2.m));

	// Apply impulse
	Vector2 impulse = normal * j;
	obj1.vel = obj1.vel + (impulse / obj1.m);
	obj2.vel = obj2.vel - (impulse / obj2.m);

	// Resolve interpenetration
	resolveInterpenetration(obj1, obj2, normal);
}

//Seperates particles so they are no longer overlapping
void PhysEngine::resolveInterpenetration(GameObject &obj1, GameObject &obj2, Vector2 normal)
{
	double pDepth = ((obj1.radius + obj2.radius) - (obj1.pos - obj2.pos).mag());	// Penetration depth
	Vector2 correction = normal * (pDepth / ((1 / obj1.m) + (1 / obj2.m))) * 0.2;	// Correction of penetration
	obj1.pos = obj1.pos - (correction / obj1.m);
	obj2.pos = obj2.pos + (correction / obj2.m);
}

//Resolves what happens when a GameObject collides with the edge of the screen
void PhysEngine::boundary(int i)
{
	Vector2 pos = gameObjects.at(i).pos;
	double radius = gameObjects.at(i).radius;
	double xBound = width / 2;
	double yBound = height / 2;
	// If GameObject leaves left or right side of screen
	if (pos.x - radius <= -xBound || pos.x + radius >= xBound)
	{
		gameObjects.at(i).vel.x = -gameObjects.at(i).vel.x;
	}
	// If GameObject leaves top or bottom of screen
	if (pos.y - radius <= -yBound || pos.y - radius >= yBound)
	{
		gameObjects.at(i).vel.y = -gameObjects.at(i).vel.y;
	}
}