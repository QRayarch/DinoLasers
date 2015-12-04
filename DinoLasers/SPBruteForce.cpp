#include "SPBruteForce.h"


SPBruteForce::SPBruteForce()
{
}


SPBruteForce::~SPBruteForce()
{
}

std::vector<std::vector<ContactManifold>> SPBruteForce::CalculateColisions(std::vector<BoundingObject*> bos) {
	std::vector<std::vector<ContactManifold>> collInd;

	for (int i = 0; i < bos.size(); i++) {
		collInd.push_back(std::vector<ContactManifold>());

		for (int j = i + 1; j < bos.size(); j++)
		{
			ContactManifold contact;
			if (bos[i]->IsColliding(bos[j], contact))//HOT
			{
				
				contact.index = j;
				collInd[i].push_back(contact);
				
				SpatialPartition::SendCollisionInfoBoth(bos[i], bos[j]);
			}
			else {
				SendCollisionInfoBothExit(bos[i], bos[j]);
			}
		}
	}

	return collInd;
}
