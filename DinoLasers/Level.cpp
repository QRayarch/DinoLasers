#include "Level.h"


Level::Level()
{
	uiElements;
}


Level::~Level()
{
	for (int e = 0; e < uiElements.size(); e++) {
		if (uiElements[e] != nullptr) {
			delete uiElements[e];
			uiElements[e] = nullptr;
		}
	}
}

void Level::AddUIElement(UI* newElement) {
	uiElements.push_back(newElement);
}

Level* Level::NextLevel() {
	return this;
}



void Level::Update(float dt) {
	for (int e = 0; e < uiElements.size(); e++) {
		uiElements[e]->Update(dt);
	}
	GameObjectManager::GetInstance()->Update(dt);
	BoundingObjectManager::GetInstance()->CheckCollisions();
}

void Level::PausedUpdate(float dt) {

}

void Level::Render() {
	GameObjectManager::GetInstance()->Render();
	BoundingObjectManager::GetInstance()->Draw();
	for (int e = 0; e < uiElements.size(); e++) {
		uiElements[e]->Render();
	}
}