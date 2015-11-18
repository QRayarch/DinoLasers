#include "CameraFollow.h"


void CameraFollow::Init(void)
{
	camera = CameraManagerSingleton::GetInstance();
	cameraSpacing = 3.0f;
	//cameraTarget = GetGameObject()->GetTransform().GetPosition();
	//cameraPosition = vector3(cameraTarget.x, cameraTarget.y + cameraSpacing, cameraTarget.z - cameraSpacing);

	//camera->SetPositionTargetAndView(cameraPosition, cameraTarget, GetGameObject()->GetTransform().GetUp());
}
void CameraFollow::Swap(CameraFollow& other)
{
	std::swap(cameraSpacing, other.cameraSpacing);
	std::swap(cameraTarget, other.cameraTarget);
	std::swap(cameraPosition, other.cameraPosition);
}

CameraFollow::CameraFollow()
{
	Init();
}

CameraFollow::CameraFollow(CameraFollow const& other)
{
	cameraSpacing = other.cameraSpacing;
	cameraTarget = other.cameraTarget;
	cameraPosition = other.cameraPosition;
}

CameraFollow& CameraFollow::operator=(CameraFollow const& other)
{
	if (this != &other)
	{
		Init();
		CameraFollow temp(other);
		Swap(temp);
	}
	return *this;
}

CameraFollow::~CameraFollow()
{
}

void CameraFollow::Update(float dt)
{

}
float CameraFollow::GetSpacing(void){ return cameraSpacing; }
void CameraFollow::SetSpacing(float s){ cameraSpacing = s; }
