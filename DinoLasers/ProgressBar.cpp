#include "ProgressBar.h"


ProgressBar::ProgressBar(String name, float maxValue) 
	: UI(name)
{
	width = 20;
	maxVal = maxValue;
	currentVal = maxVal;
	fillColor = REWHITE;
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::SetCurrentValue(float newValue) {
	currentVal = glm::clamp(newValue, 0.0f, maxVal);
}

float ProgressBar::GetCurrentValue() {
	return currentVal;
}

void ProgressBar::SetFillColor(vector3 newColor){ fillColor = newColor; }

void ProgressBar::Update(float dt) {

}

void ProgressBar::Render() {
	MeshManagerSingleton::GetInstance()->SetFont("Font_UI.png");
	String bar = "";
	float normal = currentVal / maxVal;
	float wid = width;
	for (int w = 0; w < width; w++) {
		int prog = static_cast<int>(normal * width);
		if (prog == w) {
			int next = static_cast<int>(((currentVal - (prog / wid) *  maxVal) / maxVal * wid) * 10);
			if (next >= 10) {
				bar += "0";
			}
			else if (next <= 0) {
				bar += "#";
			}
			else {
				bar += std::to_string(next);
			}
			//bar += "@";
		} else if (prog < w) {
			bar += "#";
		} else {
			bar += "0";
		}
	}
	MeshManagerSingleton::GetInstance()->PrintLine(bar, fillColor);
}