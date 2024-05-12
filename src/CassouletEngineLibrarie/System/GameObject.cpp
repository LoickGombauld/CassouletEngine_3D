#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/System/ComponentManager.h>
#include <CassouletEngineLibrarie/System/GameManager.h>

GameObject::GameObject()
{
 GameManager::Instance().createEntity(this);
}

void GameObject::UpdateSelf()
{
	GameManager::Instance().getComponentManager(id)->Update();
}

void GameObject::Draw()
{
	GameManager::Instance().getComponentManager(id)->Draw();
}

bool GameObject::HasColliders()
{
	return hasColliders;
}


GameObject::~GameObject()
{
	GameManager::Instance().destroyEntity(id);
}
