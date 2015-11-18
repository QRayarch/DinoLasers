#include "BoundingObjectManager.h"


BoundingObjectManager::BoundingObjectManager()
{
	boundingObjs = std::map<uint, BoundingObject*>();
	spatialPartition = new SPBruteForce();
	groundY = 0.0f;
	addIndex = 1;
}

BoundingObjectManager::~BoundingObjectManager() {
	std::map<uint, BoundingObject*>::iterator iterator;
	for (iterator = boundingObjs.begin(); iterator != boundingObjs.end(); iterator++) {
		if (boundingObjs[iterator->first] != nullptr) {
			delete boundingObjs[iterator->first];
			boundingObjs[iterator->first] = nullptr;
		}
	}

	if (spatialPartition != nullptr) {
		delete spatialPartition;
		spatialPartition = nullptr;
	}
}

BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BoundingObjectManager();
	}
	return instance;
}

uint BoundingObjectManager::AddBoundingObject(BoundingObject* newBoundingObject)
{
	if (newBoundingObject == nullptr) return 0;
	boundingObjs[addIndex] = newBoundingObject;
	newBoundingObject->SetId(addIndex);
	return addIndex++;
}

void BoundingObjectManager::RemoveBoundingObject(BoundingObject* boundingObject) {
	if (boundingObject == nullptr) return;

	uint key = boundingObject->GetId();
	delete boundingObjs[key];
	boundingObjs[key] = nullptr;
}

void BoundingObjectManager::Release()
{
	//TODO:REALSE MAP
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

int BoundingObjectManager::GetBoundingObjNumber()
{
	return boundingObjs.size();
}

void BoundingObjectManager::SetColor(uint id, vector3 color)
{
	if (!IsInBounds(id)) return;
	boundingObjs[id]->SetColor(color);
}

void BoundingObjectManager::CheckCollisions()
{
	std::map<uint, BoundingObject*>::iterator iterator;
	for (iterator = boundingObjs.begin(); iterator != boundingObjs.end(); iterator++) {
		float tempPosY = boundingObjs[iterator->first]->GetGameObject()->GetTransform().GetPosition().y + boundingObjs[iterator->first]->GetMin().y;
		if (tempPosY < groundY)
		{
			vector3 tempPos = boundingObjs[iterator->first]->GetGameObject()->GetTransform().GetPosition();
			tempPos.y = tempPosY + (groundY - tempPosY);
			boundingObjs[iterator->first]->GetGameObject()->GetTransform().SetPosition(tempPos);
		}
	}
	//This could be changed to be faster.
	collInd = spatialPartition->CalculateColisions(boundingObjs);
}
void BoundingObjectManager::Draw()
{
	std::map<uint, BoundingObject*>::iterator iterator;
	for (iterator = boundingObjs.begin(); iterator != boundingObjs.end(); iterator++) {
		//boundingObjs[iterator->first]->Draw();
	}
}

bool BoundingObjectManager::IsInBounds(uint id) {
	return boundingObjs.find(id) != boundingObjs.end();
}

void BoundingObjectManager::SetGroundY(float _groundY)
{
	groundY = _groundY;
}