#pragma once
#include "BoundingBox.h"

class SATBoundingBox : public BoundingBox
{
public:
	SATBoundingBox(std::vector<vector3>);
	~SATBoundingBox();

	bool IsColliding(BoundingBox* const);
};

