#include "CollisionDebug.h"


CollisionDebug::CollisionDebug()
{
}


CollisionDebug::~CollisionDebug()
{
}

void CollisionDebug::SetGameObject(GameObject* gameObject) {
	Collideable::SetGameObject(gameObject);

	BoundingObject* boundingOB = gameObject->GetComponent<BoundingObject>();
	if (boundingOB != nullptr) {
		boundingOB->SetOBBVisibility(true);
	}
}

void CollisionDebug::OnCollide(CollisionInfo info) {
	info.GetSource()->SetColor(RERED);
}

void CollisionDebug::OnCollideExit(CollisionInfo info) {
	info.GetSource()->SetColor(REWHITE);
}

void CollisionDebug::OnTrigger(CollisionInfo info) {
	info.GetSource()->SetColor(REMAGENTA);
}

void CollisionDebug::OnTriggerExit(CollisionInfo info) {
	info.GetSource()->SetColor(REWHITE);
}
