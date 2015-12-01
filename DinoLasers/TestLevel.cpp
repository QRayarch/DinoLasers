#include "TestLevel.h"


TestLevel::TestLevel()
{
}


TestLevel::~TestLevel()
{
	
}


void TestLevel::Load() {
	dino = new GameObject();
	dino->AddComponent(new ModelRender("DinoLasers\\Dino.obj", "Dino"));
	BoundingObject* dinoBO = new BoundingObject();
	dinoBO->SetLayer(2);
	dino->AddComponent(dinoBO);
	dino->AddComponent(new CameraFollow());
	ProjectileLauncher* launcher = new ProjectileLauncher();
	launcher->SetFireTime(0.1f);
	dino->AddComponent(launcher);
	dino->AddComponent(new PlayerMovement());
	dino->AddComponent(new Rigidbody());
	dino->AddComponent(new Health());
	dino->GetTransform().SetPosition(vector3(0.0f, 5.0f, 0.0f));
	//dino->AddComponent(new CollisionDebug());
	GameObjectManager::GetInstance()->AddGameObject(dino);
	
	//Component* testModel = new ModelRender("DinoLasers\\Laser.obj", "Laser");
	test = new GameObject();
	//test->AddComponent(testModel);
	//BoundingObject* testBO = new BoundingObject();
	//test->AddComponent(testBO);
	GameObjectManager::GetInstance()->AddGameObject(test);

	for (int c = 0; c < 10; c++) {
		GameObject* crate = new GameObject();
		crate->AddComponent(new ModelRender("Minecraft\\MC_Cow.obj", "Crate_" + c));
		BoundingObject* crateBO = new BoundingObject();
		crateBO->SetLayer(4 | 2);
		crate->AddComponent(crateBO);
		crate->AddComponent(new Health(30.0f));
		crate->AddComponent(new Crate());
		//crate->AddComponent(new CollisionDebug());
		crate->AddComponent(new Rigidbody());
		crate->GetTransform().SetPosition(vector3(rand() % 40 - 20, 5.0f, rand() % 40 - 20));
		crate->GetTransform().SetOrentation(quaternion(vector3(0.0f, rand() % 360, 0.0f)));

		GameObjectManager::GetInstance()->AddGameObject(crate);
	}

	ProgressBar* healthBar = new ProgressBar("Health", 100.0f);
	healthBar->SetFillColor(RERED);
	AddUIElement(healthBar);
}

void TestLevel::Update(float dt) {
	Level::Update(dt);


	MeshManagerSingleton::GetInstance()->AddPlaneToQueue(glm::rotate(glm::translate(vector3(0.0f, BoundingObjectManager::GetInstance()->GetGroundY() - 1, 0.0f)) * glm::scale(vector3(1000.0f)), 90.0f, vector3(1.0f, 0.0f, 0.0f)), REGRAY);
	test->GetTransform().SetOrentation(test->GetTransform().GetOrientation() * quaternion(vector3(0.01f, 0.01f, 0.01f)));


	ProgressBar* bar = GetUIElement<ProgressBar>("Health");
	if (bar != nullptr) {
		bar->SetCurrentValue(bar->GetCurrentValue() - 2.0f * dt);
	}
}

void TestLevel::Render() {
	Level::Render();
}
