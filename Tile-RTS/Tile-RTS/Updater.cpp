#include "Updater.h"
#include "Time.h"

#include "Debugger.h"


Updater::Updater(double ut)
{
	this->ut = ut;
	
}


Updater::~Updater()
{
}

void Updater::Update() {
	ct += Time::GetDeltaTime();
	if (ct >= ut) {
		ct = 0;
		UpdateUnits();
	}
}

void Updater::UpdateUnits() {
	if (units.size() <= 0) {
		//todo: may want to delete
		return;
	}

	int size = units.size();

	for (int i = 0; i < size; ++i) {
		Unit* unit = units.front();
		units.pop();
		if (unit->Update()) {
			units.push(unit);
		}
	}


}

double Updater::GetUpdateTime() {
	return ut;
}

void Updater::AddUnit(Unit* unit) {
	units.push(unit);
	
}


