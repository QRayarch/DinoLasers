#include "SPBruteForce.h"


SPBruteForce::SPBruteForce()
{
}


SPBruteForce::~SPBruteForce()
{
}

std::vector<std::vector<uint>> SPBruteForce::CalculateColisions(std::vector<BoundingObject*> bos) {
	std::vector<std::vector<uint>> collInd;

	for (int i = 0; i < bos.size(); i++) {
		collInd.push_back(std::vector<uint>());

		for (int j = i + 1; j < bos.size(); j++)
		{
			if (bos[i]->IsColliding(bos[j]))
			{
				collInd[i].push_back(j);
				SpatialPartition::SendCollisionInfoBoth(bos[i], bos[j]);
			}
			else {
				SendCollisionInfoBothExit(bos[i], bos[j]);
			}
		}
	}

	return collInd;
}
