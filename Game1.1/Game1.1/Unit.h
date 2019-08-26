#pragma once
class Unit
{
public:
	Unit();
	~Unit();

	//color is in hex
	int color;
	//
	int texture;
	bool selected = false;


	bool IsMovable();

protected:
	bool movable;




};

