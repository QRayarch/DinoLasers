#pragma once

#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "SATBoundingBox.h"
#include "RE\ReEngAppClass.h"
#include "Updateable.h"
#include "ModelRender.h"
#include "GameObject.h"
#include "ContactManifold.h"

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

	bool hasAlignedThisFrame = false;
	
	bool isTrigger;

	uint layer;
public:
	BoundingObject(std::vector<vector3>);
	BoundingObject();
	~BoundingObject();

	void SetGameObject(GameObject*);

	void Update(float);

	bool IsColliding(BoundingObject*, ContactManifold&);
	void SetVisibility(bool);
	void SetSphereVisibility(bool);
	void SetAABBVisibility(bool);
	void SetOBBVisibility(bool);
	void SetIsTrigger(bool);
	bool IsTrigger();
	vector3 GetGlobalCenter();
	vector3 GetMin();
	vector3 GetMax();
	vector3 GetHalfWidth();
	void SetColor(vector3);

	void SetLayer(uint);
	uint GetLayer();
};

