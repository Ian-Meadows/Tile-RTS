#include "Updater.h"
#include "Time.h"


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

}

double Updater::GetUpdateTime() {
	return ut;
}

void Updater::AddUnit(Unit* unit) {
	units.push(unit);
}


