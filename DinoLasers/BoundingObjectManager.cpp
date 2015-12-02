#include "BoundingObjectManager.h"


BoundingObjectManager::BoundingObjectManager()
{
	boundingObjs = std::vector<BoundingObject*>();
	spatialPartition = new SPBruteForce();
	groundY = 0.0f;
}

BoundingObjectManager::~BoundingObjectManager() {
	std::map<uint, BoundingObject*>::iterator iterator;
	for (int b = 0; b < boundingObjs.size(); b++) {
		if (boundingObjs[b] != nullptr) {
			delete boundingObjs[b];
			boundingObjs[b] = nullptr;
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
	boundingObjs.push_back(newBoundingObject);
	return boundingObjs.size();
}

void BoundingObjectManager::RemoveBoundingObject(BoundingObject* boundingObject) {
	if (boundingObject == nullptr) return;

	for (int b = 0; b < boundingObjs.size(); b++) {
		if (boundingObjs[b] == boundingObject) {
			//delete boundingObjs[b];
			//boundingObjs[b] = nullptr;
			boundingObjs.erase(boundingObjs.begin() + b);
			return;
		}
	}
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
	collInd = spatialPartition->CalculateColisions(boundingObjs);
	for (int c = 0; c < 0; c++) {//collInd.size()
		for (int m = 0; m < collInd[c].size(); m++) {
			vector3 pos = boundingObjs[m]->GetGameObject()->GetTransform().GetPosition();

			ContactManifold cm = collInd[c][m];

			pos -= collInd[c][m].axis * collInd[c][m].penetration;
			std::cout << "MERB " << " " << (cm.penetration * 10000000.0f) << "   " << cm.axis[0] << "   " << cm.axis[1] << "   " << cm.axis[2] << "\n";
			boundingObjs[m]->GetGameObject()->GetTransform().SetPosition(pos);
		}
	}
	for (int b = 0; b < boundingObjs.size(); b++) {
		float tempPosY = boundingObjs[b]->GetGameObject()->GetTransform().GetPosition().y - boundingObjs[b]->GetHalfWidth().y;
		if (tempPosY < groundY)
		{
			vector3 tempPos = boundingObjs[b]->GetGameObject()->GetTransform().GetPosition();
			//tempPos.y = tempPosY + (groundY - tempPosY);
			tempPos.y = groundY + boundingObjs[b]->GetHalfWidth().y;
			boundingObjs[b]->GetGameObject()->GetTransform().SetPosition(tempPos);

			//Set y velo to zero
			Rigidbody* body = boundingObjs[b]->GetGameObject()->GetComponent<Rigidbody>();
			if (body != nullptr) {
				vector3 velo = body->GetVelocity();
				if (velo.y <= 0) {
					velo.y = 0;
				}
				velo = velo * DRAG;
				body->SetVelocity(velo);
			}
		}
	}
	//This could be changed to be faster.
}
void BoundingObjectManager::Draw()
{
	
}

bool BoundingObjectManager::IsInBounds(uint id) {
	return id > 0 && id < boundingObjs.size();
}

void BoundingObjectManager::SetGroundY(float _groundY)
{
	groundY = _groundY;
}

float BoundingObjectManager::GetGroundY() { return groundY; }