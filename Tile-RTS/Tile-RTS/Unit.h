#pragma once
#include "ChunkHandler.h"
#include "Time.h"
#include <iostream>
#include <glm/glm.hpp>

class Tile;

class Unit
{
public:
	Unit(glm::ivec2 position);
	~Unit();

	//color is in hex
	int color;
	//
	int texture;
	
	int commanderID;

	bool IsMovable();

	//returns false if done updating
	virtual bool Update();

	double GetUpdateRate();

	glm::ivec2 GetPosition();

	void SetTarget(Tile* tile);
	void SetTarget(Unit* unit);
	void SetTarget(Tile* tile, Unit* unit);
	
	void Select();

	bool GetSelected();

	bool GetIsUpdating();

protected:

	bool movable;

	//update rate
	double ur;

	glm::ivec2 position;

	Tile* tileTarget = nullptr;
	Unit* unitTarget = nullptr;

	bool selected = false;

	bool isUpdating = false;

};

