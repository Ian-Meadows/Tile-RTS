#pragma once

class Commander {
public:
	Commander();
	~Commander();

	virtual void Update();

	int GetColor();

protected:
	int color;
	int totalUnits;
private:

	

};