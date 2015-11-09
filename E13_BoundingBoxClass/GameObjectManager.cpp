#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	for (int u = 0; u < updateables.size(); u++) {
		if (updateables[u] != nullptr) {
			delete updateables[u];
			updateables[u] = nullptr;
		}
	}
	for (int v = 0; v < renderables.size(); v++) {
		if (renderables[v] != nullptr) {
			delete renderables[v];
			renderables[v] = nullptr;
		}
	}
}

void GameObjectManager::Update(float dt) {
	for (int u = 0; u < updateables.size(); u++) {
		updateables[u]->Update(dt);
	}
}

void GameObjectManager::Render() {
	for (int v = 0; v < renderables.size(); v++) {
		renderables[v]->Render();
	}
}


void GameObjectManager::AddGameObject(GameObject gameObject) {
	gameObjects.push_back(gameObject);

	std::map<String, Component*> components = gameObject.GetComponents();
	std::map<String, Component*>::iterator iterator;
	for (iterator = components.begin(); iterator != components.end(); iterator++) {
		//Check for render
		if (dynamic_cast<Renderable*>(components[iterator->first])) {
			printf("foundRend");
			renderables.push_back(dynamic_cast<Renderable*>(components[iterator->first]));
		}

		//Check for update
		if (dynamic_cast<Updateable*>(components[iterator->first])) {
			printf("foundUp");
			updateables.push_back(dynamic_cast<Updateable*>(components[iterator->first]));
		}
	}
}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameObjectManager();
	}
	return instance;
}

void GameObjectManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}