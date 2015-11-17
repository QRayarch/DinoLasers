#include "Level.h"


Level::Level()
{
}


Level::~Level()
{

}

void Level::Update(float dt) {
	BoundingObjectManager::GetInstance()->CheckCollisions();
	GameObjectManager::GetInstance()->Update(dt);//TODO: ADD DELTA TIME
}

void Level::Render() {
	GameObjectManager::GetInstance()->Render();
	BoundingObjectManager::GetInstance()->Draw();
}