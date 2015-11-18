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
<<<<<<< HEAD
	dino->AddComponent(new Health());
=======
	dino->AddComponent(new PlayerMovement());
>>>>>>> a716d41c9af5e7c4568c03877f327453249e03b4
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
