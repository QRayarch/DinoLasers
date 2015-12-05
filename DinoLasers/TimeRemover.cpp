#include "TimeRemover.h"


TimeRemover::TimeRemover(float removalTime)
{
	timeBeforeRemove = removalTime;
	timer = 0;
}


TimeRemover::~TimeRemover()
{
}

void TimeRemover::Update(float dt) {
	timer += dt;
	if (timer >= timeBeforeRemove) {
		GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
	}
}
