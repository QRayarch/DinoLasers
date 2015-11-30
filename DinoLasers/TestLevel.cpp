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
	dino->AddComponent(new BoundingObject());
	dino->AddComponent(new CameraFollow());
	dino->AddComponent(new ProjectileLauncher());
	dino->AddComponent(new PlayerMovement());
	dino->AddComponent(new Rigidbody());
	dino->AddComponent(new Health());
	dino->GetTransform().SetPosition(vector3(0.0f, 5.0f, 0.0f));
	//dino->AddComponent(new CollisionDebug());
	GameObjectManager::GetInstance()->AddGameObject(dino);

	Component* testModel = new ModelRender("DinoLasers\\Laser.obj", "Laser");
	test = new GameObject();
	test->AddComponent(testModel);
	BoundingObject* testBO = new BoundingObject();
	test->AddComponent(testBO);
	GameObjectManager::GetInstance()->AddGameObject(test);


	ProgressBar* healthBar = new ProgressBar("Health", 100.0f);
	healthBar->SetFillColor(RERED);
	AddUIElement(healthBar);
}

void TestLevel::Update(float dt) {
	MeshManagerSingleton::GetInstance()->AddPlaneToQueue(glm::rotate(glm::translate(vector3(0.0f, BoundingObjectManager::GetInstance()->GetGroundY() - 1, 0.0f)) * glm::scale(vector3(1000.0f)), 90.0f, vector3(1.0f, 0.0f, 0.0f)), REGRAY);
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(vector3(0.0f, 5.0f, 7.0f)), REBLUE);
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(vector3(5.0f, 5.0f, 5.0f)), RERED);
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(vector3(-3.0f, 5.0f, 10.0f)), REYELLOW);
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(vector3(-1.0f, 5.0f, 13.0f)), REGREEN);
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(vector3(-5.0f, 5.0f, 13.0f)), REORANGE);
	Level::Update(dt);
	test->GetTransform().SetOrentation(test->GetTransform().GetOrientation() * quaternion(vector3(0.01f, 0.01f, 0.01f)));


	ProgressBar* bar = GetUIElement<ProgressBar>("Health");
	if (bar != nullptr) {
		bar->SetCurrentValue(bar->GetCurrentValue() - 2.0f * dt);
	}
}

void TestLevel::Render() {
	Level::Render();
}
