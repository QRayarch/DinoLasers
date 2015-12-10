#pragma once
#include "RE\ReEngAppClass.h"
#include "SpatialPartition.h"
#include "Octant.h"
#include "BoundingObjectManager.h"
#include "ContactManifold.h"
#include "BoundingObject.h"

class SPOctree : public SpatialPartition
{
private:
	float size;
	vector3 center;
	Octant* root;
public:
	SPOctree();
	~SPOctree();

	std::vector<std::vector<ContactManifold>> CalculateColisions(std::vector<BoundingObject*>);
	void SetSize(std::vector<BoundingObject*>);
};

