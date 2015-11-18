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
	dino->AddComponent(new Health());
	//dino->AddComponent(new CollisionDebug());
	GameObjectManager::GetInstance()->AddGameObject(dino);

	Component* testModel = new ModelRender("Minecraft\\MC_Creeper.obj", "Creeper");
	test = new GameObject();
	test->AddComponent(testModel);
	BoundingObject* testBO = new BoundingObject();
	test->AddComponent(testBO);
	GameObjectManager::GetInstance()->AddGameObject(test);
}

void TestLevel::Update(float dt) {
	MeshManagerSingleton::GetInstance()->AddPlaneToQueue(glm::rotate(matrix4(IDENTITY_M4), 90.0f, vector3(1.0f, 0.0f, 0.0f)) * glm::scale(vector3(1000.0f)), REGRAY);
	Level::Update(dt);
}

void TestLevel::Render() {
	Level::Render();
}
