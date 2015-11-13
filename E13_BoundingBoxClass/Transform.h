#pragma once
#include "RE\ReEng.h"

class Transform
{
	vector3 position;
	quaternion orientation;
	vector3 scale;
public:
	Transform();
	Transform(vector3);
	Transform(vector3, quaternion, vector3);
	Transform(Transform const&);
	~Transform();

	Transform& operator=(Transform const&);

	matrix4 GetMatrix();

	void SetPosition(vector3);
	vector3 GetPosition();
	void SetOrentation(quaternion);
	quaternion GetOrientation();
	void SetScale(vector3);
	vector3 GetScale();
	void SetPositionOrientation(vector3, quaternion);
	void SetAll(vector3, quaternion, vector3);
private:
	void Init();
	void Release();
	void Swap(Transform&);
};

