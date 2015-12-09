#include "Score.h"

Score::Score()
{
	score = 0;
}
Score::Score(float _score)
{
	score = _score;
}

float Score::GetHealth()
{
	return score;
}

void Score::AddScore(float _increment)
{
	score += _increment;
}

Score::~Score()
{
}