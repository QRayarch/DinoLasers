#include "UIButton.h"


UIButton::UIButton(String name, vector3 c1, vector3 c2) : UI(name)
{
	color1 = c1;
	color2 = c2;
	paddX = 0;
	paddY = 0;
	invisiblePadY = 0;
	isInside = false;
}


UIButton::~UIButton()
{
}

void UIButton::Update(float dt) {
	//&& x < (paddX + UI::GetName().length()) * TEXT_SIZE && y < (paddY + 3) * TEXT_SIZE
	//&& y > paddY * TEXT_SIZE
	int x = sf::Mouse::getPosition().x - SystemSingleton::GetInstance()->GetWindowX();
	int y = sf::Mouse::getPosition().y - SystemSingleton::GetInstance()->GetWindowY();
	//std::cout << x << " " << paddX * TEXT_SIZE << " " << ((paddX + UI::GetName().length() * 3)) << "\n";
	//std::cout << y << " " << (paddY * 3 * TEXT_SIZE) << " " << ((paddY + 1) * 3 * TEXT_SIZE) << "\n\n";
	//x > (paddX + UI::GetName().length())* TEXT_SIZE && x < (paddX + UI::GetName().length() * 3) * TEXT_SIZE
	if (y > ((paddY - 1 + invisiblePadY) * 3 * TEXT_SIZE) && y < ((paddY + invisiblePadY) * 3 * TEXT_SIZE) && x >(paddX + UI::GetName().length())* TEXT_SIZE && x < (paddX + UI::GetName().length() * 3) * TEXT_SIZE) {
		isInside = true;
	} else {
		isInside = false;
	}
}

bool UIButton::IsPressed(){
	if (isInside) {
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}
	return false;
}


void UIButton::Render() {
	String padding = "";
	for (int y = 0; y < paddY; y++) {
		padding += "\n";
	}
	for (int x = 0; x < paddX; x++) {
		padding += " ";
	}
	//MeshManagerSingleton::GetInstance()->AddLineToRenderList(vector3(paddX * TEXT_SIZE, paddY * TEXT_SIZE, 0.0f), vector3((paddX + UI::GetName().size()) * TEXT_SIZE, (paddY + 1) * TEXT_SIZE, 0.0f));
	MeshManagerSingleton::GetInstance()->PrintLine(padding+UI::GetName() , isInside?color2:color1);
}

void UIButton::SetPaddingX(uint pX) { paddX = pX; }

void UIButton::SetPaddingY(uint pY) { paddY = pY; }
void UIButton::SetInvisiblePaddingY(uint pY) { invisiblePadY = pY; }
