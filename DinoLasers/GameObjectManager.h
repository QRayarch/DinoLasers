#pragma once
#include "GameObject.h"
#include "Renderable.h"
#include "Updateable.h"
#include "BoundingObjectManager.h"
#include "BoundingObject.h"

class GameObjectManager
{
private:
	std::vector<GameObject*> gameObjects;
	std::vector<Updateable*> updateables;
	std::vector<Renderable*> renderables;
public:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* instance;
	static GameObjectManager* GetInstance();
	static void ReleaseInstance();

	void AddGameObject(GameObject*);
	void RemoveGameObject(GameObject*);
	void RemoveUpdateable(Updateable*);
	void RemoveRenderable(Renderable*);

	void Update(float);
	void Render();
};

