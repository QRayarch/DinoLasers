#pragma once
#include "UI.h"
class ProgressBar :
	public UI
{
public:
	ProgressBar(String, float);
	~ProgressBar();

	void Update(float);
	void Render();

	void SetCurrentValue(float);
	float GetCurrentValue();
	void SetFillColor(vector3);
private:
	int width;
	vector3 fillColor;
	float maxVal;
	float currentVal;
};

