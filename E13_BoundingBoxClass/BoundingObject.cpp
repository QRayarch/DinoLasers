#include "BoundingObject.h"


BoundingObject::BoundingObject(std::vector<vector3> vertices)
{
	modelMatrix = IDENTITY_M4;
	sphere = new BoundingSphere(vertices);
	ob = new MyBoundingBoxClass(vertices);
	realign = new MyBoundingBoxClass(vertices);

	isVisible = true;
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

void BoundingObject::Draw() {
	if (isVisible)
	{
		MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(realign->GetCenterGlobal()) * glm::scale(realign->GetHalfWidth() * 2.0f), color, WIRE);
		//MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(ob->GetCenterGlobal()) * glm::scale(ob->GetHalfWidth() * 2.0f), color, WIRE);
		MeshManagerSingleton::GetInstance()->AddSphereToQueue(glm::translate(sphere->GetCenterGlobal()) * glm::scale(vector3(sphere->GetRadius() * 2.0f)), color, WIRE);
	}
}


bool BoundingObject::IsColliding(BoundingObject* other) {
	if (!other->sphere->IsColliding(sphere)) return false;
	realign->RealignBox(ob);
	other->realign->RealignBox(other->ob);
	return other->realign->IsColliding(realign);
}

bool BoundingObject::GetVisibility() { return isVisible; }

void BoundingObject::SetVisibility(bool visible)
{
	isVisible = visible;
}

void BoundingObject::SetAABBVisibility(bool newVisibility) {
	realign->SetVisibility(newVisibility);
}

vector3 BoundingObject::GetGlobalCenter() { return sphere->GetCenterGlobal(); }
vector3 BoundingObject::GetMin() { return realign->GetMin(); }
vector3 BoundingObject::GetMax() { return realign->GetMax(); }

matrix4 BoundingObject::GetModelMatrix() { 
	return modelMatrix;
}

void BoundingObject::SetModelMatrix(matrix4 model)
{
	if (model == modelMatrix) return;

	modelMatrix = model;

	sphere->SetModelMatrix(modelMatrix);
	ob->SetModelMatrix(modelMatrix);

	//Set new Radius 
	sphere->SetRadius(glm::distance(realign->GetMax(), realign->GetCenterLocal()));
}

void BoundingObject::SetColor(vector3 newColor)
{
	color = newColor;
}