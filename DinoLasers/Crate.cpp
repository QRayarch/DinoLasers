#include "Crate.h"


Crate::Crate()
{
}

void Crate::OnDeath()
{
	int spawn = rand() % 2;//Changed to mode 3 when wall
	GameObject* spawned = new GameObject();
	BoundingObject* boundingOb = new BoundingObject();
	float s = 5000.0f;
	switch (spawn)
	{
		//Spaghetti
		case 0:
			spawned->AddComponent(new ModelRender("DinoLasers\\Spaghetti.obj", "Spaghetti"));
			boundingOb->SetIsTrigger(true);
			boundingOb->SetLayer(8);
			spawned->AddComponent(new AnimateRotation(vector3(0.0f, 1.0f, 0.0f)));
			//spawned->AddComponent(new Rigidbody());
			//spawned->AddComponent(new RandomMove(s));
			break;
		//Landmine
		case 1:
			spawned->AddComponent(new ModelRender("DinoLasers\\SpaghettiMine.obj", "Mine"));
			//boundingOb->SetIsTrigger(true);
			boundingOb->SetLayer(8);
			spawned->AddComponent(new AnimateRotation(vector3(0.0f, 2.0f, 0.0f)));
			spawned->AddComponent(new Rigidbody());
			spawned->AddComponent(new RandomMove(s));
			spawned->AddComponent(new LandMine(10));
			break;
		//Wall
		case 2:
			break;
	}
	vector3 pos = GetGameObject()->GetTransform().GetPosition();
	pos.y = 1;
	spawned->GetTransform().SetPositionOrientation(pos, GetGameObject()->GetTransform().GetOrientation());

	spawned->AddComponent(boundingOb);

	GameObjectManager::GetInstance()->AddGameObject(spawned);



	GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
}

Crate::~Crate()
{
}
