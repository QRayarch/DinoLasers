#include "SpatialPartition.h"


SpatialPartition::SpatialPartition()
{
}


SpatialPartition::~SpatialPartition()
{
}

void SpatialPartition::SendCollisionInfoBoth(BoundingObject* a, BoundingObject* b) {
	SendCollisionInfo(a, b);
	SendCollisionInfo(b, a);
}

void SpatialPartition::SendCollisionInfo(BoundingObject* source, BoundingObject* checked) {
	if (source == nullptr || checked == nullptr) return;

	CollisionInfo collisionInfo(source, checked);

	std::vector<Collideable*> sourceCollideables = source->GetGameObject()->GetComponents<Collideable>();
	if (source->IsTrigger()) {
		for (int c = 0; c < sourceCollideables.size(); c++) {
			sourceCollideables[c]->OnTrigger(collisionInfo);
		}
	}
	else {
		for (int c = 0; c < sourceCollideables.size(); c++) {
			sourceCollideables[c]->OnCollide(collisionInfo);
		}
	}
}

void SpatialPartition::SendCollisionInfoBothExit(BoundingObject* a, BoundingObject* b) {
	SendCollisionInfoExit(a, b);
	SendCollisionInfoExit(b, a);
}

void SpatialPartition::SendCollisionInfoExit(BoundingObject* source, BoundingObject* checked) {
	if (source == nullptr || checked == nullptr) return;

	CollisionInfo collisionInfo(source, checked);

	std::vector<Collideable*> sourceCollideables = source->GetGameObject()->GetComponents<Collideable>();
	if (source->IsTrigger()) {
		for (int c = 0; c < sourceCollideables.size(); c++) {
			sourceCollideables[c]->OnTriggerExit(collisionInfo);
		}
	}
	else {
		for (int c = 0; c < sourceCollideables.size(); c++) {
			sourceCollideables[c]->OnCollideExit(collisionInfo);
		}
	}
}