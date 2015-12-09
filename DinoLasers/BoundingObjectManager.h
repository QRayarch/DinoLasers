#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"
#include "SpatialPartition.h"
#include "SPBruteForce.h"
#include "Rigidbody.h"
#include "ContactManifold.h"

class BoundingObjectManager
{
	
private:
	BoundingObjectManager();
	~BoundingObjectManager();
	std::vector<BoundingObject*> boundingObjs;

	SpatialPartition* spatialPartition;
	std::vector<std::vector<ContactManifold>> collInd;
	float groundY;
public:
	static BoundingObjectManager* instance;
	static BoundingObjectManager* GetInstance();
	static void Release();
	void SetVisibility(uint, bool visible);
	uint AddBoundingObject(BoundingObject*);
	void RemoveBoundingObject(BoundingObject*);
	void SwitchBoxVisibility(uint, bool);
	int GetBoundingObjNumber();
	void SetColor(uint, vector3);
	void RenderSetting(bool);
	void RenderSetting(uint, bool);
	void CheckCollisions();
	void Draw();
	void SetModelMatrix(uint, matrix4);
	void SetGroundY(float);
	float GetGroundY();
	bool IsInBounds(uint);
};

