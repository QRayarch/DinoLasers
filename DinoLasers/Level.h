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
#include "UI.h"

class Level
{
public:
	Level();
	~Level();

	void AddUIElement(UI*);
	template<class T>
	T* GetUIElement(String name) {
		for (int e = 0; e < uiElements.size(); e++) {
			if (uiElements[e]->GetName().compare(name) == 0) {
				T* element = dynamic_cast<T*>(uiElements[e]);
				if (element != nullptr) {
					return element;
				}
				return nullptr;
			}
		}
		return nullptr;
	}

	virtual void Load() = 0;
	virtual void Update(float);
	virtual void Render();
private:
	std::vector<UI*> uiElements;
};

