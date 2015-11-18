#include "TestLevel.h"


TestLevel::TestLevel()
{
}


TestLevel::~TestLevel()
{
	
}


void TestLevel::Load() {
	Component* dinoModel = new ModelRender("DinoLasers\\Dino.obj", "Dino");
	dino = new GameObject();
	dino->AddComponent(dinoModel);
	BoundingObject* dinoBO = new BoundingObject();
	dino->AddComponent(dinoBO);
	dino->AddComponent(new CameraFollow());
	//dino->AddComponent(new Rigidbody());
	dino->AddComponent(new Health());
	dino->AddComponent(new PlayerMovement());
	dino->GetTransform().SetPosition(vector3(0.0f, 5.0f, 0.0f));
	dino->AddComponent(new CameraFollow());
	dino->AddComponent(new ProjectileLauncher());
	//dino->AddComponent(new CollisionDebug());
	GameObjectManager::GetInstance()->AddGameObject(dino);

	Component* testModel = new ModelRender("DinoLasers\\Laser.obj", "Laser");
	test = new GameObject();
	test->AddComponent(testModel);
	BoundingObject* testBO = new BoundingObject();
	test->AddComponent(testBO);
	GameObjectManager::GetInstance()->AddGameObject(test);
}

void TestLevel::Update(float dt) {
	MeshManagerSingleton::GetInstance()->AddPlaneToQueue(glm::rotate(matrix4(IDENTITY_M4), 90.0f, vector3(1.0f, 0.0f, 0.0f)) * glm::scale(vector3(1000.0f)), REGRAY);
	Level::Update(dt);
	test->GetTransform().SetOrentation(test->GetTransform().GetOrientation() * quaternion(vector3(0.01f, 0.01f, 0.01f)));
}

void TestLevel::Render() {
	Level::Render();
}
