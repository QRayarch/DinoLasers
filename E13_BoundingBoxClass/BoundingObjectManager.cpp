#include "BoundingObjectManager.h"


BoundingObjectManager::BoundingObjectManager()
{
	boundingObjs = std::map<uint, BoundingObject*>();
	addIndex = 1;
}

BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BoundingObjectManager();
	}
	return instance;
}

uint BoundingObjectManager::AddBox(std::vector<vector3> verticies)
{
	BoundingObject* bo = new BoundingObject(verticies);
	if (bo == nullptr) return 0;
	boundingObjs[addIndex] = bo;
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

void BoundingObjectManager::SwitchBoxVisibility(uint id, bool vis)
{
	if (!IsInBounds(id)) return;
	boundingObjs[id]->SetAABBVisibility(vis);
}

void BoundingObjectManager::SetVisibility(uint id, bool visible)
{
	if (!IsInBounds(id)) return;
	boundingObjs[id]->SetVisibility(visible);
}

void BoundingObjectManager::RenderSetting(bool visible)
{
	std::map<uint, BoundingObject*>::iterator iterator;
	for (iterator = boundingObjs.begin(); iterator != boundingObjs.end(); iterator++) {
		boundingObjs[iterator->first]->SetVisibility(visible);
	}
}
void BoundingObjectManager::RenderSetting(bool visible, int bo)
{
	if (!IsInBounds(bo)) return;
	boundingObjList[bo]->SetVisibility(visible);
}
void BoundingObjectManager::CheckCollisions()
{
	for (int i = 0; i < boundingObjList.size(); i++)
	{
		for (int j = i + 1; j < boundingObjList.size(); j++)
		{
			if (boundingObjList[i]->IsColliding(boundingObjList[j]))
			{
				SetColor(i, RERED);
				SetColor(j, RERED);
			}
			else
			{
				SetColor(i, REWHITE);
				SetColor(j, REWHITE);
			}
		}
	}
}
void BoundingObjectManager::Draw()
{
	for (int i = 0; i < boundingObjList.size(); i++)
	{
		boundingObjList[i]->Draw();
	}
}


void BoundingObjectManager::SetModelMatrix(int bo, matrix4 model)
{
	if (!IsInBounds(bo)) return;
	boundingObjList[bo]->SetModelMatrix(model);
}

bool BoundingObjectManager::IsInBounds(int bo) {
	return bo > -1 && bo < boundingObjList.size();
}
