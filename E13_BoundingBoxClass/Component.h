#pragma once
#ifndef Component_h  
#define Component_h  

class GameObject;

#include "GameObject.h"

class Component
{
private:
	GameObject gameObject;
public:
	Component();
	Component(const Component&);
	~Component();

	GameObject GetGameObject();
	void SetGameObject(GameObject);
};

#endif

