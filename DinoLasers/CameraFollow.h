#pragma once

#include "Updateable.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class CameraFollow : public Updateable
{
private:
	float cameraSpacing;
	vector3 cameraTarget;
	vector3 cameraPosition;	
public:
	CameraFollow();
	CameraFollow(CameraFollow const&);
	CameraFollow& operator=(CameraFollow const&);
	~CameraFollow();
	void Update(float);

	float GetSpacing(void);
	void SetSpacing(float);
	
protected:
	void Init(void);
	void Swap(CameraFollow&);
	CameraManagerSingleton* camera;
};

