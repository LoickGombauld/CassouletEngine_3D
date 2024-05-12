#include<CassouletEngineLibrarie/System/GameManager.h>
#include <CassouletEngineLibrarie/System/GameObject.h>

void GameManager::createEntity(GameObject* obj) {
    auto id = registry.create();
    obj->manager = GameManager::Instance().addComponentManager(id);
    obj->id = id;
    registry.emplace<GameObject*>(id,obj);
}



void GameManager::destroyEntity(entt::entity& entity) {

    registry.destroy(entity);
}

void GameManager::DrawAllGameObjects()
{
    for (auto i : registry.view<GameObject*>())
    {
     auto & obj =  registry.get<GameObject*>(i);
     if (obj->enabled)
     {
         obj->Draw();
     }
    }
}

void GameManager::UpdateAllGameObjects()
{
    for (auto i : registry.view<GameObject*>())
    {
        auto& obj = registry.get<GameObject*>(i);
        if (obj->enabled)
        {
            obj->UpdateSelf();
        }
    }
}

ComponentManager* GameManager::addComponentManager(entt::entity& entity) {
    ComponentManager component;
    return &registry.emplace<ComponentManager>(entity, component);
}

GameObject* GameManager::getGameObject(entt::entity& entity) {
    return registry.get<GameObject*>(entity);
}

ComponentManager* GameManager::getComponentManager(entt::entity& entity) {
    return &registry.get<ComponentManager>(entity);
}