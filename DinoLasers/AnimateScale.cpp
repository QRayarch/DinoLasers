#include "AnimateScale.h"


AnimateScale::AnimateScale(vector3 from, vector3 to, float time)
{
	fromScale = from;
	toScale = to;
	animateOver = time;
	animateTimer = 0;
}


AnimateScale::~AnimateScale()
{
}

void AnimateScale::Update(float dt) {
	animateTimer += dt;
	if (animateTimer < animateOver) {
		GetGameObject()->GetTransform().SetScale(glm::lerp(fromScale, toScale, animateTimer / animateOver));
	}
}
