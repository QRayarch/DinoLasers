#pragma once
#include "RE\ReEngAppClass.h"

class GameObject;

class Component
{
private:
	GameObject* gameObject;
public:
	Component();
	Component(const Component&);
	~Component();

	GameObject* GetGameObject();
	void SetGameObject(GameObject*);

	virtual String GetType() = 0;
};

