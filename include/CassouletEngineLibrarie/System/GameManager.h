#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/System/Component.h>
#include <CassouletEngineLibrarie/System/ComponentManager.h>

class CASSOULET_DLL GameManager {

public:
	static GameManager& Instance() {
		static GameManager instance;
		return instance;
	}

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void createEntity(GameObject* obj);

	void destroyEntity(entt::entity& entity);
	
	void UpdateAllGameObjects();
	void DrawAllGameObjects();

	ComponentManager* addComponentManager(entt::entity& entity);

	GameObject* getGameObject(entt::entity& entity);

	ComponentManager* getComponentManager(entt::entity& entity);

	void removeComponent(entt::entity& entity, const std::string& componentName) {
		auto it = getComponentManager(entity)->m_ComponentManagers.find(componentName);
		assert(it != getComponentManager(entity)->m_ComponentManagers.end() && "Component not found in map");
		getComponentManager(entity)->m_ComponentManagers.erase(componentName);
	}


	template <class T>
	typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type AddComponent(entt::entity& entity, T* component)
	{
		component->gameObject = getGameObject(entity);

		getComponentManager(entity)->m_ComponentManagers[component->GetName()] = component;


		// Insérer le composant dans le registre
		registry.emplace<T*>(entity, component);

		// Retourner le pointeur vers le composant nouvellement créé
		return component;
	}


	template <class T>
	typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type AddComponent(entt::entity& entity)
	{
		T* component = new T();
		component->gameObject = getGameObject(entity);

		// Insérer le composant dans le registre
		registry.emplace<T>(entity, *component);

		// Insérer le composant dans le gestionnaire de composants
		getComponentManager(entity)->m_ComponentManagers[component->GetName()] = component;

		// Retourner le pointeur vers le composant nouvellement créé
		return component;
	}

	template <class T>
	inline typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type getComponent(entt::entity& entity)
	{
		return &registry.get<T>(entity);
	}

	// Méthode qui utilise la fonction view pour obtenir une vue sur les entités avec certains composants
	template <class... T>
	decltype(auto) getEntitiesByType() {
		return registry.view<T...>();
	}


private:
	GameManager() = default;
	~GameManager() = default;



	entt::registry registry;

};