#pragma once

#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "SATBoundingBox.h"
#include "RE\ReEngAppClass.h"
#include "Updateable.h"
#include "ModelRender.h"
#include "GameObject.h"

class BoundingObject : public Updateable
{
private:
	BoundingSphere* sphere;
	SATBoundingBox* ob;
	BoundingBox* realign;
	vector3 color;

	bool isSphereVisible;
	bool isAABBVisible;
	bool isOBBVisible;
	
	bool isTrigger;

	uint id;
public:
	BoundingObject(std::vector<vector3>);
	BoundingObject();
	~BoundingObject();

	void SetGameObject(GameObject*);

	void Update(float);

	bool IsColliding(BoundingObject*);
	void SetVisibility(bool);
	void SetSphereVisibility(bool);
	void SetAABBVisibility(bool);
	void SetOBBVisibility(bool);
	void SetIsTrigger(bool);
	bool IsTrigger();
	vector3 GetGlobalCenter();
	vector3 GetMin();
	vector3 GetMax();
	void SetColor(vector3);

	uint GetId();
	void SetId(uint);
};

