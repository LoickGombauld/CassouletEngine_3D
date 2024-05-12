#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

class GameObject;

class CASSOULET_DLL Component
{
private:
	//called every frame
	virtual void Update() { };

	//we have two draw methods so things that are important to draw last like transparent textures and collider wireframes can use Draw2 and everything else Draw1
	//called every frame before Draw2()
	virtual void Draw() { };

public:

	//if false the update and draw methods is not called
	bool enabled = true;

	//the game object the component is on
	GameObject* gameObject = nullptr;

	//if a component has not overwritten GetName we throw an exception to let them know
	virtual const std::string GetName() { throw "Component does not have a name"; };

	//We hide the Update method behind V_Update because when a method is public and virtual it is always visible outside the dll and we dont want that.
	//by doing it this way all other classes in the engine can still call the Update method using V_Update without it being visible to the user outside the dll
	void V_Update();

	//same explanation as above
	void V_Draw();
};