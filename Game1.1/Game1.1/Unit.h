#pragma once
#include "ChunkHandler.h"
#include "Time.h"
#include <iostream>
#include <glm/glm.hpp>

class Unit
{
public:
	Unit(glm::ivec2 position);
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

	glm::ivec2 GetPosition();

protected:

	bool movable;

	//update rate
	double ur;

	glm::ivec2 position;


};

