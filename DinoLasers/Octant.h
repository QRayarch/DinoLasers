#pragma once

#include "RE\ReEng.h"

class Octant
{
	static uint maxSubLevel;	
public:
	Octant(vector3, float);
	Octant(Octant const& other);
	Octant& operator=(Octant const& other);
	~Octant(void);
	void Swap(Octant& other);
	float GetSize(void);
	void SetSize(float);
	vector3 GetCenter(void);
	void SetCenter(vector3);
	void Display(vector3 color = REDEFAULT);
	void Subdivide(void);
	Octant* GetChild(uint);
	void KillBranch(void);
	bool CanSubDivide();
	bool IsLeaf();
private:
	uint level = 0;
	uint numChildren = 0;
	Octant* parent;
	Octant* children[8];

	float size = 0.0f;

	MeshManagerSingleton* meshManager = nullptr;

	vector3 center = vector3(0.0f);
	void Release(void);
	void Init(void);
};

