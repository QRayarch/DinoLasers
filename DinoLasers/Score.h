#pragma once
#include "Component.h"
#include "math.h"
//#include "DeathHandler.h"
#include "GameObject.h"
//#include "Crate.h"

class Score : public Component
{
private:
	float score;
public:
	Score();
	Score(float);
	~Score();
	float GetScore();
	void AddScore(float);
};