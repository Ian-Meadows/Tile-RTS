#include "TestButton.h"


TestButton::TestButton() : Button(ButtonPosition::TopLeft, glm::vec2(50, 20), 0.15f)
{
	buttonColor = 0x00ffff;
	textColor = glm::vec3(0, 0, 0);
	SetText("Hello, World!");
}


TestButton::~TestButton()
{
}


void TestButton::ButtonPressed() {
	buttonColor = 0x00ff00;
}
void TestButton::ButtonReleased() {
	buttonColor = 0xff0000;
}
void TestButton::MouseEntered() {
	buttonColor = 0x0000ff;
}
void TestButton::MouseExited() {
	buttonColor = 0x00ffff;
}
