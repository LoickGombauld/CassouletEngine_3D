#pragma once

#include <CassouletEngineLibrarie/Math/Transform.h>

class ComponentManager;
class Component;

class CASSOULET_DLL  GameObject
{
public:
	GameObject();
   ~GameObject();

   ComponentManager* manager;

	//if false the game object and its ComponentManagers will not be updated or drawn
	bool enabled = true;
	entt::entity id;
	//game object tag. use to quickly identify type of game object
	std::string tag = "NO TAG";

	Transform transform;

	//update the game object
	void UpdateSelf();

	//call ComponentManagers draw method
	void Draw();

	//returns true if the game object has a collider on it
	bool HasColliders();


	//returns the distance to the active camera
	float GetDistanceToCamera() const;


	void AddComponent(Component* component);

	void GetComponent(Component* component);

private:

	//true if the game object has a collider
	bool hasColliders = false;

	//distance to the active camera
	float distanceToCamera;


};