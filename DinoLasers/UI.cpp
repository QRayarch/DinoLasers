#include "UI.h"


UI::UI(String newName)
{
	name = newName;
}


UI::~UI()
{
}

void UI::Update(float dt) {

}

String UI::GetName() { return name; }
