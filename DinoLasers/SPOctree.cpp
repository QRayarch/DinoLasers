#include "SPOctree.h"


SPOctree::SPOctree()
{
	//size = 0.0f;
	//center = vector3(0.0f);
	root = new Octant(center, size);
}


SPOctree::~SPOctree()
{
}

std::vector<std::vector<ContactManifold>> SPOctree::CalculateColisions(std::vector<BoundingObject*> bos)
{
	std::vector<std::vector<ContactManifold>> collInd;
	
	SetSize(bos);
	FindWithin(bos, root);
	
	for (int i = 0; i < 8; i++)
	{
		FindWithin(bos, root->GetChild(i));
		root->GetChild(i)->Display(REGREEN);
	}
	root->Display(RERED);	

	for (int i = 0; i < bos.size(); i++) {
		collInd.push_back(std::vector<ContactManifold>());
	}
	return collInd;
}

void SPOctree::SetSize(std::vector<BoundingObject*> bos)
{
	min = bos[0]->GetMinGlobal();
	max = bos[0]->GetMaxGlobal();
	for (int i = 1; i < bos.size(); i++)
	{
		if (bos[i]->GetMinGlobal().x < min.x)
		{
			min.x = bos[i]->GetMinGlobal().x;
		}
		if (bos[i]->GetMinGlobal().y < min.y)
		{
			min.y = bos[i]->GetMinGlobal().y;
		}
		if (bos[i]->GetMinGlobal().z < min.z)
		{
			min.z = bos[i]->GetMinGlobal().z;
		}
		if (bos[i]->GetMaxGlobal().x > max.x)
		{
			max.x = bos[i]->GetMaxGlobal().x;
		}
		if (bos[i]->GetMaxGlobal().y > max.y)
		{
			max.y = bos[i]->GetMaxGlobal().y;
		}
		if (bos[i]->GetMaxGlobal().z > max.z)
		{
			max.z = bos[i]->GetMaxGlobal().z;
		}
	}
	
	//float dX = max.x - min.x;
	//float dY = max.y - min.y;
	//float dZ = max.z - min.z;
	//
	//if (dX > dY) size = dX;
	//if (dX > dZ) size = dX;
	//if (dY > dX) size = dY;
	//if (dY > dZ) size = dY;
	//if (dZ > dX) size = dZ;
	//if (dZ > dY) size = dZ;

	if (min.x < min.y) min.y = min.x;
	if (min.y < min.x) min.x = min.y;
	if (min.x < min.z) min.z = min.x;
	if (min.z < min.x) min.x = min.z;
	if (min.y < min.z) min.z = min.y;
	if (min.z < min.y) min.y = min.z;
	
	if (max.x > max.y) max.y = max.x;
	if (max.y > max.x) max.x = max.y;
	if (max.x > max.z) max.z = max.x;
	if (max.z > max.x) max.x = max.z;
	if (max.y > max.z) max.z = max.y;
	if (max.z > max.y) max.y = max.z;

	size = glm::distance(vector3(min.x, 0.0f, 0.0f), vector3(max.x, 0.0f, 0.0f));

	//std::cout << "\n" << size << "\n";
	center = (min + max) / 2.0f;
	root->SetSize(size/2);
	root->SetCenter(center);
}

void SPOctree::FindWithin(std::vector<BoundingObject*> bos, Octant* oct)
{
	int inCounter = 0;
	vector3 octMin = vector3(oct->GetSize() / 2) + oct->GetCenter();
	vector3 octMax = vector3(-(oct->GetSize() / 2)) + oct->GetCenter();

	for (int i = 0; i < bos.size(); i++)
	{
		if (bos[i]->GetMinGlobal().x < octMax.x)
		{
			inCounter++;
		}
		else if (bos[i]->GetMaxGlobal().x > octMin.x)
		{
			inCounter++;
		}
		else if (bos[i]->GetMinGlobal().y < octMax.y)
		{
			inCounter++;
		}
		else if (bos[i]->GetMaxGlobal().y > octMin.y)
		{
			inCounter++;
		}
		else if (bos[i]->GetMinGlobal().z < octMax.z)
		{
			inCounter++;
		}
		else if (bos[i]->GetMaxGlobal().z > octMin.z)
		{
			inCounter++;
		}
	}
	std::cout << "Within: " << inCounter << std::endl;

	if (inCounter > 5)
	{
		oct->Subdivide();
	}
}

