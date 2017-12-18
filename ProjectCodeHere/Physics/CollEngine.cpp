#include <cmath>
#include <iostream>
#include "CollEngine.h"

CollEngine::CollEngine()
{

}

CollEngine::CollEngine(std::vector<GameObject> &gameObjects, int &w, int &h)
{
	std::cout << "CollEngine called" << std::endl;
	list = gameObjects;
	listSize = 0;
	width = w;
	height = h;
	std::cout << "CollEngine finished" << std::endl;
}

CollEngine::~CollEngine()
{
}

//	Stores unique pairs in uniquePairs list
void CollEngine::getUniquePairs()
{
	if (listSize != list.size())
	{
		int size = list.size();
		listSize = size;
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				uniquePairs.push_back(Pair(list.at(i), list.at(j)));
			}
		}
	}	
}

//Broadphase collision detection
void CollEngine::broadphase()
{
	getUniquePairs();
	GameObject obj1;
	GameObject obj2;
	for (int i = 0; i < uniquePairs.size(); i++)
	{
		obj1 = uniquePairs[i].obj1;
		obj2 = uniquePairs[i].obj2;

		// If the bounding spheres intersect, send them to narrowphase
		if (pow(obj1.bound + obj2.bound, 2) > (obj1.pos - obj2.pos).mag2())
		{
			narrowphase(uniquePairs[i]);
		}
	}
}

//Narrowphase collision detection
void CollEngine::narrowphase(Pair pair)
{
	//	If circles representing objects intersect, resolve collision
	if (pow(pair.obj1.radius + pair.obj2.radius, 2) > (pair.obj1.pos - pair.obj2.pos).mag2())
	{
		collide(pair);
	}
}

Vector2 CollEngine::getCollisionNormal(Pair pair)
{
	return (pair.obj1.pos - pair.obj2.pos).norm();
}

double CollEngine::getImpulse(Pair pair, Vector2 hat)
{
	GameObject obj1 = pair.obj1;
	GameObject obj2 = pair.obj2;
	return (obj1.m*obj2.m*(1+0.95)*((obj1.vel*hat)-(obj2.vel*hat)))/(obj1.m + obj2.m);
}

//Resolves collision of two GameObjects
void CollEngine::collide(Pair pair)
{
	Vector2 hat = getCollisionNormal(pair);
	double impulse = getImpulse(pair, hat);
	pair.obj1.vel = pair.obj1.vel + (hat*(impulse / pair.obj1.m));
	pair.obj2.vel = pair.obj2.vel - (hat*(impulse / pair.obj2.m));
	resolveInterpenetration(pair, hat, impulse);
}

//Seperates particles so they are no longer overlapping
void CollEngine::resolveInterpenetration(Pair pair, Vector2 hat, double impulse)
{
	double dL = (pair.obj1.radius + pair.obj2.radius) - (pair.obj1.pos - pair.obj2.pos).mag2();	// Change in length
	pair.obj1.pos = pair.obj1.pos + (hat*((pair.obj1.m*dL) / (pair.obj1.m + pair.obj2.m)));
	pair.obj2.pos = pair.obj2.pos - (hat*((pair.obj2.m*dL) / (pair.obj1.m + pair.obj2.m)));
}

//Resolves what happens when a GameObject collides with the edge of the screen
void CollEngine::boundary(int i)
{
	Vector2 pos = list.at(i).pos;
	double radius = list.at(i).radius;
	double xBound = width / 2;
	double yBound = height / 2;
	if (pos.x - radius <= -xBound || pos.x + radius >= xBound)
	{
		list.at(i).vel.x = -list.at(i).vel.x;
	}
	if (pos.y - radius <= -yBound || pos.y - radius >= yBound)
	{
		list.at(i).vel.y = -list.at(i).vel.y;
	}
}