#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	for (int g = 0; g < gameObjects.size(); g++) {
		if (gameObjects[g] != nullptr) {
			delete gameObjects[g];
			gameObjects[g] = nullptr;
		}
	}

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


void GameObjectManager::AddGameObject(GameObject* gameObject) {
	gameObjects.push_back(gameObject);

	std::vector<Component*> components = gameObject->GetComponents();
	for (int v = 0; v < components.size(); v++) {
		//Check for render
		Renderable* ren = dynamic_cast<Renderable*>(components[v]);
		if (ren != nullptr) {
			printf("foundRend ");
			renderables.push_back(ren);
		}

		//Check for update
		Updateable* up = dynamic_cast<Updateable*>(components[v]);
		if (up != nullptr) {
			printf("foundUp ");
			updateables.push_back(up);
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