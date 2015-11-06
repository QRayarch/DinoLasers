#pragma once

#include "RE\ReEngAppClass.h"
#include "BoundingObject.h"

class BoundingObjectManager
{
	
private:
	BoundingObjectManager();
	std::map<uint, BoundingObject*> boundingObjs;
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
	void RenderSetting(bool, int);
	void CheckCollisions();
	void Draw();
	void SetModelMatrix(uint, matrix4);

	bool IsInBounds(int);
};

