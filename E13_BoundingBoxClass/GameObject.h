#pragma once
#ifndef GameObject_h  
#define GameObject_h  
#include "RE\ReEngAppClass.h"

//class Component;

//#include "Component.h"

class GameObject
{
private:
	matrix4 worldMatrix;
	int components;
//	std::map<String, Component> components;
public:
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
	GameObject& operator=(const GameObject&);

	matrix4 GetWorldMatrix();
	void SetWorldMatrix(matrix4);
};

#endif
