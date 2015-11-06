#pragma once

#include "BoundingSphere.h"
#include "MyBoundingBoxClass.h"
#include "RE\ReEngAppClass.h"


class BoundingObject
{
private:
	BoundingSphere* sphere;
	MyBoundingBoxClass* ob;
	MyBoundingBoxClass* realign;

	bool isVisible;
	vector3 color;
	matrix4 modelMatrix;
public:
	BoundingObject(std::vector<vector3>);
	~BoundingObject();

	void Draw();
	bool IsColliding(BoundingObject*);
	bool GetVisibility();
	void SetVisibility(bool);
	void SetAABBVisibility(bool);
	vector3 GetGlobalCenter();
	vector3 GetMin();
	vector3 GetMax();
	matrix4 GetModelMatrix();
	void SetModelMatrix(matrix4);
	void SetColor(vector3);
};

