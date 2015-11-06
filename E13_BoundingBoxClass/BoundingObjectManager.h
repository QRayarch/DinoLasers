#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"
#include "SpatialPartition.h"
#include "SPBruteForce.h"

class BoundingObjectManager
{
	
private:
	BoundingObjectManager();
	~BoundingObjectManager();
	std::map<uint, BoundingObject*> boundingObjs;

	SpatialPartition* spatialPartition;
	std::map<uint, std::vector<uint>> collInd;

	int addIndex;
public:
	static BoundingObjectManager* instance;
	static BoundingObjectManager* GetInstance();
	static void Release();
	void SetVisibility(uint, bool visible);
	uint AddBox(std::vector<vector3>);
	void SwitchBoxVisibility(uint, bool);
	int GetBoundingObjNumber();
	void SetColor(uint, vector3);
	void RenderSetting(bool);
	void RenderSetting(uint, bool);
	void CheckCollisions();
	void Draw();
	void SetModelMatrix(uint, matrix4);

	bool IsInBounds(uint);
};

