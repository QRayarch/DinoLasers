#pragma once

#include "RE\ReEngAppClass.h"
#include "SpatialPartition.h"
#include "BoundingObject.h"

class SPBruteForce : public SpatialPartition
{
public:
	SPBruteForce();
	~SPBruteForce();
	
	std::map<uint, std::vector<uint>> CalculateColisions(std::map<uint, BoundingObject*>);
};

