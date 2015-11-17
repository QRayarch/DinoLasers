#include "BoundingObjectManager.h"


BoundingObjectManager::BoundingObjectManager()
{
	boundingObjs = std::map<uint, BoundingObject*>();
	spatialPartition = new SPBruteForce();

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
	//This could be changed to be faster.
	collInd = spatialPartition->CalculateColisions(boundingObjs);

	/*
	//Everything down is temp for testing
	std::map<uint, BoundingObject*>::iterator i;
	std::map<uint, BoundingObject*>::iterator j;
	for (i = boundingObjs.begin(); i != boundingObjs.end(); i++) {
		j = i;
		j++;
		for (; j != boundingObjs.end(); j++)
		{
			SetColor(i->first, REWHITE);
			SetColor(j->first, REWHITE);
		}
	}
	std::map<uint, BoundingObject*>::iterator col;
	for (col = boundingObjs.begin(); col != boundingObjs.end(); col++) {
		for (int i = 0; i < collInd[col->first].size(); i++) {
			SetColor(collInd[col->first][i], RERED);
			SetColor(col->first, RERED);
		}
	}*/
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
