#include <CassouletEngineLibrarie/System/ComponentManager.h>
#include <CassouletEngineLibrarie/System/Component.h>
#include <CassouletEngineLibrarie/System/GameManager.h>

ComponentManager::~ComponentManager()
{
	std::unordered_map<std::string, Component*>::iterator com = m_ComponentManagers.begin();
	while (com != m_ComponentManagers.end())
	{
		 delete	com->second;
		com++;
	}
	m_ComponentManagers.clear();
}

//called every frame
void ComponentManager::Update() {
	std::unordered_map<std::string, Component*>::iterator com = m_ComponentManagers.begin();
	while (com != m_ComponentManagers.end())
	{
		if (com->second->enabled) {
			com->second->V_Update();
			com->second->gameObject = GameManager::Instance().getGameObject(com->second->gameObject->id);
		}
		com++;
	}
};


//called every frame
void ComponentManager::Draw() {
	std::unordered_map<std::string, Component*>::iterator com = m_ComponentManagers.begin();
	while (com != m_ComponentManagers.end())
	{
		if (com->second->enabled)
			com->second->V_Draw();
		com++;
	}
};