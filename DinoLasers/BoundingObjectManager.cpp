#include "BoundingObjectManager.h"


BoundingObjectManager::BoundingObjectManager()
{
	boundingObjs = std::vector<BoundingObject*>();
	spatialPartition = new SPOctree();

	groundY = 0.0f;
}

BoundingObjectManager::~BoundingObjectManager() {
	Clear();

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
	for (int c = 0; c < collInd.size(); c++) {
		for (int m = 0; m < collInd[c].size(); m++) {
			if (IsInBounds(collInd[c][m].index)) {
				if (!boundingObjs[c]->IsTrigger() && !boundingObjs[collInd[c][m].index]->IsTrigger()) {// && boundingObjs[c]->GetLayer() & boundingObjs[m]->GetLayer()
					if (boundingObjs[c]->IsMoveable()) {
						vector3 pos = boundingObjs[c]->GetGameObject()->GetTransform().GetPosition();

						pos -= collInd[c][m].axis * collInd[c][m].penetration;
						//std::cout << "MERB " << " " << (cm.penetration * 10000000.0f) << "   " << cm.axis[0] << "   " << cm.axis[1] << "   " << cm.axis[2] << "\n";
						boundingObjs[c]->GetGameObject()->GetTransform().SetPosition(pos);
						//boundingObjs[c]->GetGameObject()->GetTransform().RecalculateMatrix();
					} else if (false && boundingObjs[collInd[c][m].index]->IsMoveable()){
						vector3 pos = boundingObjs[collInd[c][m].index]->GetGameObject()->GetTransform().GetPosition();

						pos -= collInd[c][m].axis * collInd[c][m].penetration;
						//boundingObjs[collInd[c][m].index]->GetGameObject()->GetTransform().SetPosition(pos);
					}
				}
			}
		}
	}
	for (int b = 0; b < boundingObjs.size(); b++) {
		if (boundingObjs[b]->IsMoveable()) {
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

void BoundingObjectManager::Clear(){
	boundingObjs.clear();
	std::map<uint, BoundingObject*>::iterator iterator;
	for (int b = 0; b < boundingObjs.size(); b++) {
		if (boundingObjs[b] != nullptr) {
			delete boundingObjs[b];
			boundingObjs[b] = nullptr;
		}
	}
}
