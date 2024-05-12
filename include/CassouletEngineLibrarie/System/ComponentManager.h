#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

class Component;

class CASSOULET_DLL ComponentManager
{
public:
	ComponentManager() {};
	~ComponentManager();
	//if false the update and draw methods is not called
	bool enabled = true;
	//called every frame
	void Update();

	//called every frame
	void Draw();

	std::unordered_map <std::string,Component* > m_ComponentManagers;
};