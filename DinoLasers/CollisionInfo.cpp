#include "CollisionInfo.h"


CollisionInfo::CollisionInfo(BoundingObject* src, BoundingObject* chked)
{
	source = src;
	checked = chked;
}


CollisionInfo::~CollisionInfo()
{
}

BoundingObject* CollisionInfo::GetSource() { return source; }
BoundingObject* CollisionInfo::GetChecked() { return checked; }
