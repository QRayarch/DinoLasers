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

			//Create a explosion
			vector3 originalSize = vector3(0.0f, 0.0f, 0.0f);
			vector3 endingSize = vector3(2.0f, 2.0f, 2.0f);
			float timeAnimateOver = 0.2f;
			GameObject* exp = new GameObject();
			exp->AddComponent(new ModelRender("DinoLasers\\Explosion.obj", "Explosion"));
			exp->AddComponent(new AnimateScale(originalSize, endingSize, timeAnimateOver));
			exp->AddComponent(new TimeRemover(timeAnimateOver));
			exp->GetTransform().SetScale(originalSize);
			vector3 pos = GetGameObject()->GetTransform().GetPosition();
			pos.y = 0;
			exp->GetTransform().SetPosition(pos);
			exp->GetTransform().RecalculateMatrix();
			GameObjectManager::GetInstance()->AddGameObject(exp);
		}
		GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
	}
}
