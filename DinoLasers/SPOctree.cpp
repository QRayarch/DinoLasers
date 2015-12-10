#include "SPOctree.h"


SPOctree::SPOctree()
{
	size = 0.0f;
	center = vector3(0.0f);
	root = new Octant(center, size);
}


SPOctree::~SPOctree()
{
}

std::vector<std::vector<ContactManifold>> SPOctree::CalculateColisions(std::vector<BoundingObject*> bos)
{
	std::vector<std::vector<ContactManifold>> collInd;

	SetSize(bos);
	for (int i = 0; i < bos.size(); i++)
	{

	}

	for (int i = 0; i < bos.size(); i++) {
		collInd.push_back(std::vector<ContactManifold>());
	}
	return collInd;
}

void SPOctree::SetSize(std::vector<BoundingObject*> bos)
{
	vector3 min = bos[0]->GetMin();
	vector3 max = bos[0]->GetMax();

	for (int i = 0; i < bos.size(); i++)
	{
		if (bos[i]->GetMin().x < min.x)
		{
			min.x = bos[i]->GetMin().x;
		}
		if (bos[i]->GetMin().y < min.y)
		{
			min.y = bos[i]->GetMin().y;
		}
		if (bos[i]->GetMin().z < min.z)
		{
			min.z = bos[i]->GetMin().z;
		}
		if (bos[i]->GetMax().x > max.x)
		{
			max.x = bos[i]->GetMax().x;
		}
		if (bos[i]->GetMax().y > max.y)
		{
			max.y = bos[i]->GetMax().y;
		}
		if (bos[i]->GetMax().z > max.z)
		{
			max.z = bos[i]->GetMax().z;
		}
	}

	if (min.x < min.y) min.y = min.x;
	if (min.y < min.x) min.x = min.y;
	if (min.x < min.z) min.x = min.z;
	if (min.z < min.x) min.z = min.x;
	if (min.y < min.z) min.z = min.y;
	if (min.z < min.y) min.y = min.z;

	if (max.x > max.y) max.y = max.x;
	if (max.y > max.x) max.x = max.y;
	if (max.x > max.z) max.x = max.z;
	if (max.z > max.x) max.z = max.x;
	if (max.y > max.z) max.z = max.y;
	if (max.z > max.y) max.y = max.z;

	size = glm::distance(vector3(min.x, 0.0f, 0.0f), vector3(max.x, 0.0f, 0.0f));
	center = (min + max) / 2.0f;
	root->SetSize(size);
	root->SetCenter(center);
}

