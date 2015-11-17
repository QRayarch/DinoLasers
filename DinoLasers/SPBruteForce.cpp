#include "SPBruteForce.h"


SPBruteForce::SPBruteForce()
{
}


SPBruteForce::~SPBruteForce()
{
}

std::map<uint, std::vector<uint>> SPBruteForce::CalculateColisions(std::map<uint, BoundingObject*> bos) {
	//ASK ALBERTO about maybe using a heap here?
	std::map<uint, std::vector<uint>> collInd;

	std::map<uint, BoundingObject*>::iterator i;
	std::map<uint, BoundingObject*>::iterator j;
	for (i = bos.begin(); i != bos.end(); i++) {
		collInd[i->first] = (std::vector<uint>());
		j = i;
		j++;
		for (; j != bos.end(); j++)
		{
			if (bos[i->first]->IsColliding(bos[j->first]))
			{
				collInd[i->first].push_back(j->first);
				SpatialPartition::SendCollisionInfoBoth(bos[i->first], bos[j->first]);
			}
			else {
				SendCollisionInfoBothExit(bos[i->first], bos[j->first]);
			}
		}
	}

	return collInd;
}
