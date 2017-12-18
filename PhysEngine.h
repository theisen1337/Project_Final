#pragma once

#include <vector>
#include "Vector2.h"
#include "GameObject.h"

class PhysEngine
{

	private:
		Vector2 gravity;
		double dt;
		std::vector<GameObject> gameObjects;
		int listSize;					//	Size of the list vector; used to check if unique pairs need to be recomputed
		int width, height;

	public:
		//	Constructors
		PhysEngine();
		PhysEngine(double deltaTime, int w, int h);
		~PhysEngine();

		//	Phys Engine Functions
		void setGravity(Vector2 g);
		void addForce(int i, Vector2 force);
		void netForce(int i);
		void addGameObject(GameObject go);
		void removeGameObject();
		void printGameObjects();
		void forceGravity(int i);
		void beuler(int i);
		void verlet(int i);
		void updateVertices();
		void update();

		// Collision Engine Functions
		void broadphase();
		void narrowphase(GameObject &obj1, GameObject &obj2);
		Vector2 getCollisionNormal(GameObject &obj1, GameObject &obj2);
		void collide(GameObject &obj1, GameObject &obj2);
		void resolveInterpenetration(GameObject &obj1, GameObject &obj2, Vector2 normal);
		void boundary(int i);
};