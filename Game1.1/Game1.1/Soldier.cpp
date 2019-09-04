#include "Soldier.h"
#include <iostream>


Soldier::Soldier(glm::ivec2 pos) : Unit()
{
	color = 0xf0f000;

	texture = ChunkHandler::GetTextureAtlas()->GetImageLocation("Circle");

	movable = true;

	this->pos = pos;
}


Soldier::~Soldier()
{
}

void Soldier::Update() {
	time += Time::GetDeltaTime();

	if (time >= 0.1f) {
		time = 0;
		
		//ChunkHandler::MoveUnit(pos, glm::ivec2(pos.x + 1, pos.y));
		//pos = glm::ivec2(pos.x + 1, pos.y);

		
	}
}
