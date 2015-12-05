#pragma once
#include "Updateable.h"
#include "GameObjectManager.h"

class TimeRemover :
	public Updateable
{
public:
	TimeRemover(float);
	~TimeRemover();

	void Update(float);
private:
	float timeBeforeRemove;
	float timer;
};

