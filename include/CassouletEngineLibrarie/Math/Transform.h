#pragma once

#include <CassouletEngineLibrarie/Math/Vector3.h>

//responsible for keeping track of a game objects position, scale and rotation in the game world
class CASSOULET_DLL Transform
{
public:

	//game object world position
	Vector3 position = Vector3(0, 0, 0);
	//game object world scale
	Vector3 scale = Vector3(1, 1, 1);
	//game object world rotation
	Vector3 rotation;

	void Translate(Vector3 translation);

	Vector3 RotateTransform(Vector3 axis, float angle);

	//returns a vector pointing up relative to the position and rotation of the game object
	Vector3 Up();
	//returns a vector pointing down relative to the position and rotation of the game object
	Vector3 Down();
	//returns a vector pointing right relative to the position and rotation of the game object
	Vector3 Right();
	//returns a vector pointing left relative to the position and rotation of the game object
	Vector3 Left();
	//returns a vector pointing forward relative to the position and rotation of the game object
	Vector3 Forward();
	//returns a vector pointing back relative to the position and rotation of the game object
	Vector3 Back();
};