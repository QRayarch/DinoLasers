#pragma once
#include "UI.h"
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#define TEXT_SIZE 12

class UIButton :
	public UI
{
public:
	UIButton(String, vector3, vector3);
	~UIButton();
	void Update(float);
	void Render();
	void SetPaddingX(uint);
	void SetPaddingY(uint);
	void SetInvisiblePaddingY(uint);
	bool IsPressed();
private:
	vector3 color1;
	vector3 color2;
	uint paddX;
	uint paddY;
	uint invisiblePadY;
	bool isInside;
};

