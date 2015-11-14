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
	virtual void SetGameObject(GameObject*);
};

