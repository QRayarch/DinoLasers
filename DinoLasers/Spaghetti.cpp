#include "Spaghetti.h"

Spaghetti::Spaghetti(float pts)
{
	points = pts;
}

Spaghetti::~Spaghetti()
{
}

void Spaghetti::OnTrigger(CollisionInfo info) {
	Score* score = info.GetChecked()->GetGameObject()->GetComponent<Score>();
	if (score != nullptr)
	{
		score->AddScore(points);
		GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
		std::cout << "Score: " << score->GetScore() << "\n";
	}
}
