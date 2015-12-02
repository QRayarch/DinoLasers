#include "SATBoundingBox.h"


SATBoundingBox::SATBoundingBox(std::vector<vector3> verts) 
	:BoundingBox(verts)
{
}


SATBoundingBox::~SATBoundingBox()
{
	BoundingBox::~BoundingBox();
}

SATBoundingBox::SATBoundingBox(SATBoundingBox const& other) 
	: BoundingBox(other)
{
	
}

SATBoundingBox& SATBoundingBox::operator=(SATBoundingBox const& other)
{
	return static_cast<SATBoundingBox&>(BoundingBox::operator=(other));
}

bool SATBoundingBox::IsColliding(BoundingBox* const colliding, ContactManifold& contact) {
	return CheckSATCollision(colliding, contact);
}

bool SATBoundingBox::DoesUseSAT() {
	return true;
}
