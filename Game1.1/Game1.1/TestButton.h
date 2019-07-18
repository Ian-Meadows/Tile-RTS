#pragma once
#include "Button.h"
class TestButton :
	public Button
{
public:
	TestButton();
	~TestButton();

	void ButtonPressed();
	void ButtonReleased();
	void MousedEntered();
	void MouseExited();
};

