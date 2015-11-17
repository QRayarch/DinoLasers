#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"
#include "Collideable.h"
#include "CollisionInfo.h"

class SpatialPartition
{
public:
	SpatialPartition();
	~SpatialPartition();

	virtual std::map<uint, std::vector<uint>> CalculateColisions(std::map<uint, BoundingObject*>) = 0;

	void SendCollisionInfoBoth(BoundingObject*, BoundingObject*);
	void SendCollisionInfoBothExit(BoundingObject*, BoundingObject*);
private :
	void SendCollisionInfo(BoundingObject*, BoundingObject*);
	void SendCollisionInfoExit(BoundingObject*, BoundingObject*);
};

