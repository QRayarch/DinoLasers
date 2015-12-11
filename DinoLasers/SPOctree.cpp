#include "SPOctree.h"


SPOctree::SPOctree()
{
	//size = 0.0f;
	//center = vector3(0.0f);
	root = new Octant(center, size);
	maxBOPerOctant = 4;
}


SPOctree::~SPOctree()
{
}

std::vector<std::vector<ContactManifold>> SPOctree::CalculateColisions(std::vector<BoundingObject*> bos)
{
	std::vector<std::vector<ContactManifold>> collInd;
	std::vector<uint> indexs = std::vector<uint>(bos.size());
	for (int i = 0; i < bos.size(); i++) {
		indexs.push_back(i);
		collInd.push_back(std::vector<ContactManifold>());
	}
	SetSize(bos);	
	CalculateOctant(collInd,root,bos, indexs);
	//root->Display(REWHITE);
	return collInd;
}

void SPOctree::SetSize(std::vector<BoundingObject*> bos)
{
	if (bos.size() == 0) return;
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

	size = max.x - min.x;// ::distance(vector3(min.x, 0.0f, 0.0f), vector3(max.x, 0.0f, 0.0f));

	//std::cout << "\n" << size << "\n";
	center = min + size / 2.0f;
	root->SetSize(size/2);
	root->SetCenter(center);
}

void SPOctree::CalculateOctant(std::vector<std::vector<ContactManifold>>& collInd, Octant* octant, std::vector<BoundingObject*>& bos, std::vector<uint>& indexs)
{
	if (octant == nullptr) return;
	if (octant->CanSubDivide() && indexs.size() > maxBOPerOctant) {
		octant->Subdivide();
		for (int o = 0; o < 8; o++){
			//std::vector<BoundingObject*> newBos = std::vector<BoundingObject*>();
			std::vector<uint> newIndexs = std::vector<uint>();
			vector3 octMax = vector3(octant->GetChild(o)->GetSize()) + octant->GetChild(o)->GetCenter();
			vector3 octMin = vector3(-(octant->GetChild(o)->GetSize())) + octant->GetChild(o)->GetCenter();
			//octant->GetChild(o)->Display(REMAGENTA);
			for (int b = 0; b < indexs.size(); b++) {
				if (bos[indexs[b]]->GetMinGlobal().x < octMax.x && bos[indexs[b]]->GetMaxGlobal().x > octMin.x &&
					bos[indexs[b]]->GetMinGlobal().y < octMax.y && bos[indexs[b]]->GetMaxGlobal().y > octMin.y &&
					bos[indexs[b]]->GetMinGlobal().z < octMax.z && bos[indexs[b]]->GetMaxGlobal().z > octMin.z)
				{
					newIndexs.push_back(indexs[b]);
				}
			}
			CalculateOctant(collInd, octant->GetChild(o), bos, newIndexs);
		}
	} else if(octant->IsLeaf()) {
		//Look for collisions
		for (int i = 0; i < indexs.size(); i++) {
			uint a = indexs[i];
			for (int j = i + 1; j < indexs.size(); j++)
			{
				uint b = indexs[j];
				if (b != a) {
					bool isNoDup = true;
					for (int c = 0; c < collInd[a].size(); c++) {
						if (collInd[a][c].index == b) {
							isNoDup = false;
							c = collInd[a].size();
						}
					}
					if (isNoDup) {
						ContactManifold contact;
						if (bos[a]->IsColliding(bos[b], contact))//HOT
						{

							contact.index = b;
							collInd[a].push_back(contact);

							SpatialPartition::SendCollisionInfoBoth(bos[a], bos[b]);
						}
						else {
							SendCollisionInfoBothExit(bos[a], bos[b]);
						}
					}
					
				}
				
			}
		}
	}
}

