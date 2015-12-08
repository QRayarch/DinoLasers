#include "CrateDropper.h"


CrateDropper::CrateDropper(float addTime, uint numCrates)
{
	crateAddTime = addTime;
	crateAddTimer = 0;
	maxNumberOfCrates = numCrates;
}


CrateDropper::~CrateDropper()
{
}

void CrateDropper::Update(float dt) {
	crateAddTimer += dt;
	if (crateAddTimer >= crateAddTime) {
		uint numCrates = GameObjectManager::GetInstance()->GetObjectsWithTag("Crate").size();
		if (numCrates < maxNumberOfCrates) {
			SpawnCrate();
		}
		crateAddTimer = 0;
	}
}

void CrateDropper::AddSpawnPoint(vector3 spawn) {
	spawnPoints.push_back(spawn);
}

void CrateDropper::SpawnCrate() {
	if (spawnPoints.size() == 0) {
		std::cout << "--No spawn points--//CrateDropper has no spawn points, try adding some spawn points.\n";
		return;
	}
	GameObject* crate = new GameObject();
	crate->SetTag("Crate");
	crate->AddComponent(new ModelRender("DinoLasers\\Crate.obj", "Crate"));
	BoundingObject* crateBO = new BoundingObject();
	crateBO->SetLayer(4 | 2);
	crate->AddComponent(crateBO);
	crate->AddComponent(new Health(50.0f));
	crate->AddComponent(new Crate());
	crate->AddComponent(new Rigidbody());
	crate->GetTransform().SetPosition(spawnPoints[rand() % spawnPoints.size()]);
	crate->GetTransform().SetOrentation(quaternion(vector3(0.0f, rand() % 360, 0.0f)));

	GameObjectManager::GetInstance()->AddGameObject(crate);
}
