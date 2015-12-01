#pragma once

#include "RE\ReEngAppClass.h"
#include "SpatialPartition.h"
#include "BoundingObject.h"

class SPBruteForce : public SpatialPartition
{
public:
	SPBruteForce();
	~SPBruteForce();
	
	std::vector<std::vector<uint>> CalculateColisions(std::vector<BoundingObject*>);
};

