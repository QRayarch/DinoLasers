#pragma once

#include "Updateable.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class CameraFollow : public Updateable
{
private:
	float cameraSpacing;
	float camHeight;
	float slerpDamping;
	vector3 cameraTarget;
	vector3 cameraPosition;	
	vector3 prevCamPosition;
public:
	CameraFollow();
	CameraFollow(CameraFollow const&);
	CameraFollow& operator=(CameraFollow const&);
	~CameraFollow();
	void Update(float);
	void UpdateCamera(float);

	float GetSpacing(void);
	void SetSpacing(float);
	float GetSlerpDamping(void);
	void SetSlerpDamping(float);

	void SetGameObject(GameObject*);
	
protected:
	void Init(void);
	void Swap(CameraFollow&);
	CameraManagerSingleton* camera;
};

