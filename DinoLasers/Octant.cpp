#include "Octant.h"
uint Octant::maxSubLevel = 3;
void Octant::Init(void)
{
	level = 0;
	numChildren = 0;
	center = vector3(0.0f);

	size = 0.0f;

//	meshManager = MeshManagerSingleton::GetInstance();

	parent = nullptr;

	for (uint nChild = 0; nChild < 8; nChild++)
	{
		children[nChild] = nullptr;
	}
}
void Octant::Swap(Octant& other)
{
	std::swap(level, other.level);
	std::swap(numChildren, other.numChildren);
	std::swap(center, other.center);
	std::swap(size, other.size);

	std::swap(meshManager, other.meshManager);
}
void Octant::Release(void)
{
	if (level == 0)
		KillBranch();

	/* No pointers allocated yet */
}
Octant::Octant(vector3 _center, float _size)
{
	Init();
	center = _center;
	size = _size;

	//meshManager = MeshManagerSingleton::GetInstance();
}
Octant::Octant(Octant const& other)
{
	level = other.level;
	center = other.center;
	size = other.size;
	numChildren = other.numChildren;
	meshManager = other.meshManager;

}
Octant& Octant::operator=(Octant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Octant temp(other);
		Swap(temp);
	}
	return *this;
}
Octant::~Octant(void){ Release(); }
void Octant::Display(vector3 color)
{

	for (uint nChild = 0; nChild < numChildren; nChild++)
	{
		children[nChild]->Display(color);
	}
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate(center) * glm::scale(vector3(size * 2.0f)), color, WIRE);
}

void Octant::Subdivide(void)
{
	//if (level >= m_nMaxSubLevel)
	//	return;

	numChildren = 8;

	uint nIndex = 0;
	float fNewSize = size / 2.0f;

	vector3 vCenter = center + vector3(fNewSize, fNewSize, fNewSize);
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(-fNewSize, fNewSize, fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(-fNewSize, -fNewSize, fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(fNewSize, -fNewSize, fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(fNewSize, fNewSize, -fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(-fNewSize, fNewSize, -fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(-fNewSize, -fNewSize, -fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;

	vCenter = center + vector3(fNewSize, -fNewSize, -fNewSize);
	nIndex++;
	children[nIndex] = new Octant(vCenter, fNewSize);
	children[nIndex]->parent = this;
	children[nIndex]->level = level + 1;
}

Octant* Octant::GetChild(uint nIndex)
{
	if (nIndex >= 8)
		return nullptr;

	return children[nIndex];
}

void Octant::KillBranch(void)
{
	for (uint nChild = 0; nChild < numChildren; nChild++)
	{
		children[nChild]->KillBranch();
	}
	for (uint nChild = 0; nChild < numChildren; nChild++)
	{
		if (children[nChild] != nullptr)
		{
			delete children[nChild];
			children[nChild] = nullptr;
		}
	}
}
float Octant::GetSize(void) { return size; }
void Octant::SetSize(float s) { size = s; }
vector3 Octant::GetCenter(void) { return center; }
void Octant::SetCenter(vector3 c) { center = c; }