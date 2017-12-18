#pragma once

#include <vector>
#include "GameObject.h"

class CollEngine
{
	struct Pair
	{
		GameObject obj1;
		GameObject obj2;

		Pair(GameObject &go1, GameObject &go2)
		{
			obj1 = go1;
			obj2 = go2;
		}
	};

	private:
		std::vector<GameObject> list;	//	Reference to vector of GameObjects stored in PhysEngine
		std::vector<Pair> uniquePairs;	//	Unique pairs of GameObjects used to check for collisions
		int listSize;					//	Size of the list vector; used to check if unique pairs need to be recomputed
		int width, height;				//	Width and height of the window

	public:
		CollEngine();
		CollEngine(std::vector<GameObject> &gameObjects, int &w, int &h);
		~CollEngine();
		void getUniquePairs();
		void broadphase();
		void narrowphase(Pair pair);
		Vector2 getCollisionNormal(Pair pair);
		double getImpulse(Pair pair, Vector2 hat);
		void collide(Pair pair);
		void resolveInterpenetration(Pair pair, Vector2 hat, double impulse);
		void boundary(int i);
};