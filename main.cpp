#include <iostream>
#include "Vector2.h"
#include "GameObject.h"
#include "PhysEngine.h"

using namespace std;

int main()
{
	Vector2 vec1 = Vector2(-1, -0.2);
	Vector2 vec2 = Vector2(1, 0);
	Vector2 vec3 = Vector2(1, 0.2);
	Vector2 vec4 = Vector2(-1, 0);
	cout << "Vec1: " <<vec1.toString() << endl;
	cout << "Vec1 Norm: " << vec1.norm().toString() << endl;

	GameObject part1 = GameObject(1, vec1, vec2);
	GameObject part2 = GameObject(1, vec3, vec4);
	cout << "\n" << part1.toString();

	PhysEngine eng = PhysEngine();
	eng.setGravity(Vector2(0, -1));
	eng.addGameObject(part1);
	eng.addGameObject(part2);

	cout << endl << "Before update:" << endl;
	eng.printGameObjects();

	eng.update();
	eng.update();
	eng.update();

	cout << endl << "After update:" << endl;
	eng.printGameObjects();

	return 0;
}