#pragma once
#include "Updateable.h"
#include "GameObjectManager.h"
#include "Health.h"
#include "Crate.h"
#include "Rigidbody.h"

class CrateDropper : virtual public Updateable
{
public:
	CrateDropper(float, uint);
	~CrateDropper();

	void Update(float);
	void AddSpawnPoint(vector3);
private:
	std::vector<vector3> spawnPoints;
	float crateAddTimer;
	float crateAddTime;
	uint maxNumberOfCrates;

	void SpawnCrate();
};

