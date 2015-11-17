#pragma once
#include "GameObject.h"
#include "BoundingObject.h"

class CollisionInfo
{
public:
	CollisionInfo(BoundingObject*, BoundingObject*);
	~CollisionInfo();

	BoundingObject* GetSource();
	BoundingObject* GetChecked();
private: 
	BoundingObject* source;
	BoundingObject* checked;
};

