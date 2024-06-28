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

float GameObject::GetDistanceToCamera() const
{
	return distanceToCamera;
}

void GameObject::AddComponent(Component* component)
{
	GameManager::Instance().AddComponent(id, component);
}

GameObject::~GameObject()
{
	delete(manager);
	GameManager::Instance().destroyEntity(id);
}
