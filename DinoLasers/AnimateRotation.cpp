#include "AnimateRotation.h"


AnimateRotation::AnimateRotation(vector3 rots)
{
	rotationRates = rots;
}


AnimateRotation::~AnimateRotation()
{
}

void AnimateRotation::Update(float dt) {
	quaternion ort = GetGameObject()->GetTransform().GetOrientation();
	GetGameObject()->GetTransform().SetOrentation(ort * quaternion(rotationRates * dt));
}
