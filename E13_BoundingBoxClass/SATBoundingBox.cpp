#include "SATBoundingBox.h"


SATBoundingBox::SATBoundingBox(std::vector<vector3> verts) 
	:BoundingBox(verts)
{
}


SATBoundingBox::~SATBoundingBox()
{
}

bool SATBoundingBox::IsColliding(BoundingBox* const colliding) {
	return CheckSATCollision(colliding);
}

bool SATBoundingBox::DoesUseSAT() {
	return true;
}
