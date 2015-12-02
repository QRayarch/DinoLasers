#pragma once

#include "RE\ReEngAppClass.h"
#include "SpatialPartition.h"
#include "BoundingObject.h"

class SPBruteForce : public SpatialPartition
{
public:
	SPBruteForce();
	~SPBruteForce();
	
	std::vector<std::vector<ContactManifold>> CalculateColisions(std::vector<BoundingObject*>);
};

