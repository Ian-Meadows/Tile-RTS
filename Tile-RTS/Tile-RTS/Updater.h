#pragma once
#include <queue>

#include "Unit.h"

class Updater
{
public:
	Updater(double updateTime);
	~Updater();

	void Update();

	double GetUpdateTime();

	void AddUnit(Unit* unit);

private:
	//update time
	double ut;
	//current time
	double ct = 0;

	void UpdateUnits();

	std::queue<Unit*> units;
};

