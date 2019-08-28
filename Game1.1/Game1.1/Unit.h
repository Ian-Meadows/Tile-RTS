#pragma once
#include "ChunkHandler.h"
#include "Time.h"


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

	virtual void Update();


protected:
	bool movable;




};

