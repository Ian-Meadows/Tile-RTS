#pragma once

#include "Commander.h"

namespace CommanderHandler{
	void Init();
	void Update();
	void Uninit();

	void AddCommander(Commander* commander);

	Commander* GetCommander(int index);
}