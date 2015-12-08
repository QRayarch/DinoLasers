#include "CameraFollow.h"


void CameraFollow::Init(void)
{	
	camera = CameraManagerSingleton::GetInstance();
	cameraSpacing = 6.0f;
	camHeight = 3.0f;
	cameraTarget = vector3(0.f, 0.f, 0.f);
	prevCamPosition = cameraPosition = vector3(0.f, 0.f, 0.f);
	slerpDamping = 4.0f;
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
	UpdateCamera(dt);
}

void CameraFollow::UpdateCamera(float dt)
{
	cameraTarget = GetGameObject()->GetTransform().GetPosition() + vector3(0.0f, 1.0f, 0.0f);
	float posHeight = GetGameObject()->GetTransform().GetPosition().y + camHeight;
	cameraPosition = cameraTarget - GetGameObject()->GetTransform().GetForward() * cameraSpacing;
	cameraPosition.y = posHeight;

	cameraPosition = glm::mix(prevCamPosition, cameraPosition, slerpDamping * dt);
	prevCamPosition = cameraPosition;

	camera->SetPositionTargetAndView(cameraPosition, cameraTarget, REAXISY);
}

void CameraFollow::SetGameObject(GameObject* g)
{
	Updateable::SetGameObject(g);	
}
float CameraFollow::GetSpacing(void){ return cameraSpacing; }
void CameraFollow::SetSpacing(float s){ cameraSpacing = s; }
float CameraFollow::GetSlerpDamping(void){ return slerpDamping; }
void CameraFollow::SetSlerpDamping(float d){ slerpDamping = d; }
