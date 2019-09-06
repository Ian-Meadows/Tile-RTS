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

	//returns false if done updating
	virtual bool Update();

	double GetUpdateRate();

protected:
	bool movable;

	//update rate
	double ur;


};

