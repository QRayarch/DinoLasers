#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"

class SpatialPartition
{
public:
	SpatialPartition();
	~SpatialPartition();

	virtual std::map<uint, std::vector<uint>> CalculateColisions(std::map<uint, BoundingObject*>) = 0;
};

