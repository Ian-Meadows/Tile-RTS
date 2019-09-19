#pragma once

class Commander {
public:
	Commander();
	~Commander();

	virtual void Update();

	int GetColor();

	int ID;

protected:
	int color;
	int totalUnits;
private:

	

};