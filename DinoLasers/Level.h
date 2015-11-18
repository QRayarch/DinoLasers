#pragma once

#include "BoundingObjectManager.h"
#include "GameObjectManager.h"
#include "BoundingObject.h"
#include "BoundingBox.h"
#include "GameObject.h"
#include "Renderable.h"
#include "Updateable.h"
#include "ModelRender.h"
#include "Rigidbody.h"
#include "PlayerMovement.h"
#include "CameraFollow.h"

class Level
{
public:
	Level();
	~Level();

	virtual void Load() = 0;
	virtual void Update(float);
	virtual void Render();
};

