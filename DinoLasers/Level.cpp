#include "Level.h"


Level::Level()
{
}


Level::~Level()
{

}

void Level::Update(float dt) {
	GameObjectManager::GetInstance()->Update(dt);
	BoundingObjectManager::GetInstance()->CheckCollisions();
}

void Level::Render() {
	GameObjectManager::GetInstance()->Render();
	BoundingObjectManager::GetInstance()->Draw();
}