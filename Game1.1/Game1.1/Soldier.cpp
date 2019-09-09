#include "Soldier.h"



Soldier::Soldier(glm::ivec2 position) : Unit(position)
{
	
	color = 0xf0f000;

	texture = ChunkHandler::GetTextureAtlas()->GetImageLocation("Circle");

	movable = true;

	ur = 0.1;
	
}


Soldier::~Soldier()
{
}

bool Soldier::Update() {
	ChunkHandler::MoveUnit(position, glm::ivec2(position.x + 1, position.y));
	position = glm::ivec2(position.x + 1, position.y);

	return true;
}
