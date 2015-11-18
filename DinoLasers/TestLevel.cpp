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
	dino->AddComponent(new Rigidbody());
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
	Level::Update(dt);
	test->GetTransform().SetOrentation(test->GetTransform().GetOrientation() * quaternion(vector3(0.01f, 0.01f, 0.01f)));
}

void TestLevel::Render() {
	Level::Render();
}
