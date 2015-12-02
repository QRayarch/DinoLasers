#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"
#include "Collideable.h"
#include "CollisionInfo.h"
#include "ContactManifold.h"

class SpatialPartition
{
public:
	SpatialPartition();
	~SpatialPartition();

	virtual std::vector<std::vector<ContactManifold>> CalculateColisions(std::vector<BoundingObject*>) = 0;

	void SendCollisionInfoBoth(BoundingObject*, BoundingObject*);
	void SendCollisionInfoBothExit(BoundingObject*, BoundingObject*);
private :
	void SendCollisionInfo(BoundingObject*, BoundingObject*);
	void SendCollisionInfoExit(BoundingObject*, BoundingObject*);
};

