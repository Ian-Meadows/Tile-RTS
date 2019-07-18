#include "TestButton.h"


TestButton::TestButton() : Button(ButtonPosition::Bottom, glm::vec2(50, 20), 0.15f)
{
	buttonColor = 0x00ffff;
	SetText("Hello, World!");
}


TestButton::~TestButton()
{
}


void TestButton::ButtonPressed() {

}
void TestButton::ButtonReleased() {

}
void TestButton::MousedEntered() {
	std::cout << "Hi\n";
}
void TestButton::MouseExited() {

}
