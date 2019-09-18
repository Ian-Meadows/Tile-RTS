#pragma once

namespace Time {
	double GetFPS();
	double GetDeltaTime();

	//bool is for debug purposes. if true fps will print every second
	void Init(bool);

	void Update();
}

