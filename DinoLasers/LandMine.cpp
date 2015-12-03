#include "LandMine.h"


LandMine::LandMine(float dmg)
{
	damage = dmg;
}


LandMine::~LandMine()
{
}

void LandMine::OnCollide(CollisionInfo info) {
	Health* health = info.GetChecked()->GetGameObject()->GetComponent<Health>();
	if (health != nullptr) {
		health->TakeDamage(damage);
		Rigidbody* body = info.GetChecked()->GetGameObject()->GetComponent<Rigidbody>();
		if (body != nullptr) {
			vector3 diff = info.GetChecked()->GetGameObject()->GetTransform().GetPosition() - GetGameObject()->GetTransform().GetPosition();
			diff = glm::normalize(diff);
			float amount = 40.0f;
			diff.y = 1;
			diff = diff * amount;
			body->SetVelocity(body->GetVelocity() + diff);
		}
		GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
	}
}
