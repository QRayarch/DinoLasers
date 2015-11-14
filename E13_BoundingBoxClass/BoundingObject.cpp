#include "BoundingObject.h"


BoundingObject::BoundingObject(std::vector<vector3> vertices)
{
	id = 0;
	sphere = new BoundingSphere(vertices);
	ob = new SATBoundingBox(vertices);
	realign = new BoundingBox(vertices);

	isSphereVisible = false;
	isAABBVisible = false;
	isOBBVisible = false;

	color = REWHITE;
}

//Use when you want to construct the collision info off of a model render
BoundingObject::BoundingObject()
{
	id = 0;
	sphere = nullptr;
	ob = nullptr;
	realign = nullptr;

	isSphereVisible = false;
	isAABBVisible = false;
	isOBBVisible = false;

	color = REWHITE;
}

BoundingObject::~BoundingObject()
{
	if (sphere != nullptr) {
		delete sphere;
		sphere = nullptr;
	}

	if (ob != nullptr) {
		delete ob;
		ob = nullptr;
	}

	if (realign != nullptr) {
		delete realign;
		realign = nullptr;
	}
}

void BoundingObject::SetGameObject(GameObject* gameObject) {
	Updateable::SetGameObject(gameObject);
	//Set up a bounding object around the gameobject
	if (sphere == nullptr) {
		ModelRender* modelRender = GetGameObject()->GetComponent<ModelRender>();
		if (modelRender != nullptr) {

			std::vector<vector3> vertices = MeshManagerSingleton::GetInstance()->GetVertexList(modelRender->GetModel());

			sphere = new BoundingSphere(vertices);
			ob = new SATBoundingBox(vertices);
			realign = new BoundingBox(vertices);

			color = REWHITE;
		}
	}

	sphere->SetGameObject(gameObject);
	realign->SetGameObject(gameObject);
	ob->SetGameObject(gameObject);
}

void BoundingObject::Update(float dt) {

	//Set new Radius 
	//sphere->SetRadius(glm::distance(realign->GetMax(), realign->GetCenterLocal()));
	ob->Update(dt);

	if (isSphereVisible) {
		MeshManagerSingleton::GetInstance()->AddSphereToQueue(glm::translate(sphere->GetCenterGlobal()) * glm::scale(vector3(sphere->GetRadius() * 2.0f)), color, WIRE);
	}
	if (isAABBVisible) {
		MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(realign->GetCenterGlobal()) * glm::scale(realign->GetHalfWidth() * 2.0f), color, WIRE);
	}
	if (isOBBVisible) {
		MeshManagerSingleton::GetInstance()->AddCubeToQueue(GetGameObject()->GetWorldMatrix() * glm::translate(vector3(0, ob->GetHalfWidth().y, 0)) * glm::scale(ob->GetHalfWidth() * 2.0f), color, WIRE);
	}
	
}


bool BoundingObject::IsColliding(BoundingObject* other) {
	if (!other->sphere->IsColliding(sphere)) return false;
	realign->RealignBox(ob);
	other->realign->RealignBox(other->ob);
	if (!other->realign->IsColliding(realign)) return false;
	return other->ob->CheckSATCollision(ob);
}

void BoundingObject::SetVisibility(bool isVis) { SetSphereVisibility(isVis); SetAABBVisibility(isVis); SetOBBVisibility(isVis); }
void BoundingObject::SetSphereVisibility(bool isVis) { isSphereVisible = isVis; }
void BoundingObject::SetAABBVisibility(bool isVis) { isAABBVisible = isVis; }
void BoundingObject::SetOBBVisibility(bool isVis) { isOBBVisible = isVis;  }

vector3 BoundingObject::GetGlobalCenter() { return sphere->GetCenterGlobal(); }
vector3 BoundingObject::GetMin() { return realign->GetMin(); }
vector3 BoundingObject::GetMax() { return realign->GetMax(); }

void BoundingObject::SetColor(vector3 newColor)
{
	color = newColor;
}

uint BoundingObject::GetId() { return id; }
void BoundingObject::SetId(uint newID) { id = newID; }