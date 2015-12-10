#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	Clear();
}

void GameObjectManager::Update(float dt) {
	for (int g = 0; g < gameObjects.size(); g++) {
		gameObjects[g]->GetTransform().RecalculateMatrix();
	}
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
			renderables.push_back(ren);
		}

		//Check for update
		Updateable* up = dynamic_cast<Updateable*>(components[v]);
		if (up != nullptr) {
			updateables.push_back(up);
		}
		//Check for boundingObject
		BoundingObject* boundingOb = dynamic_cast<BoundingObject*>(components[v]);
		if (boundingOb != nullptr) {
			BoundingObjectManager::GetInstance()->AddBoundingObject(boundingOb);
		}
	}
}

void GameObjectManager::RemoveGameObject(GameObject* gameObject) {
	std::vector<Component*> components = gameObject->GetComponents();
	for (int v = 0; v < components.size(); v++) {
		//Check for render
		Renderable* ren = dynamic_cast<Renderable*>(components[v]);
		if (ren != nullptr) {
			RemoveRenderable(ren);
		}

		//Check for update
		Updateable* up = dynamic_cast<Updateable*>(components[v]);
		if (up != nullptr) {
			RemoveUpdateable(up);
		}
		//Check for boundingObject
		BoundingObject* boundingOb = dynamic_cast<BoundingObject*>(components[v]);
		if (boundingOb != nullptr) {
			BoundingObjectManager::GetInstance()->RemoveBoundingObject(boundingOb);
		}
	}

	for (int g = 0; g < gameObjects.size(); g++) {
		if (gameObjects[g] == gameObject) {
			gameObjects.erase(gameObjects.begin() + g);
			return;
		}
	}
}

void GameObjectManager::RemoveUpdateable(Updateable* updateable) {
	if (updateable == nullptr) return;
	for (int u = 0; u < updateables.size(); u++)  {
		if (updateables[u] == updateable) {
			updateables.erase(updateables.begin() + u);
			return;
		}
	}
}

void GameObjectManager::RemoveRenderable(Renderable* renderable) {
	if (renderable == nullptr) return;
	for (int v = 0; v < renderables.size(); v++)  {
		if (renderables[v] == renderable) {
			renderables.erase(renderables.begin() + v);
			return;
		}
	}
}

std::vector<GameObject*> GameObjectManager::GetObjectsWithTag(String tag) {
	std::vector<GameObject*> tagged;
	for (int g = 0; g < gameObjects.size(); g++) {
		if (gameObjects[g] != nullptr && gameObjects[g]->GetTag().compare(tag) == 0) {
			tagged.push_back(gameObjects[g]);
		}
	}
	return tagged;
}

void GameObjectManager::Clear() {
	gameObjects.clear();
	updateables.clear();
	renderables.clear();
	for (int g = 0; g < gameObjects.size(); g++) {
		if (gameObjects[g] != nullptr) {
			delete gameObjects[g];
			gameObjects[g] = nullptr;
		}
	}

	/*for (int u = 0; u < updateables.size(); u++) {
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
	}*/
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