#include "Soldier.h"
#include "CommanderHandler.h"
#include "Tile.h"

Soldier::Soldier(glm::ivec2 position) : Unit(position)
{
	commanderID = 0;
	color = CommanderHandler::GetCommander(commanderID)->GetColor();

	texture = ChunkHandler::GetTextureAtlas()->GetImageLocation("Circle");

	movable = true;

	ur = 0.1;
	
}


Soldier::~Soldier()
{
}

bool Soldier::Update() {
	isUpdating = true;
	
	if (unitTarget != nullptr) {
		return true;
	}
	else if (tileTarget != nullptr) {
		glm::ivec2 tilePos = tileTarget->GetPosition();
		if (tilePos.x > position.x) {
			MoveRight();
		}
		else if(tilePos.x < position.x) {
			MoveLeft();
		}
		else {
			if (tilePos.y > position.y) {
				MoveUp();
			}
			else if (tilePos.y < position.y) {
				MoveDown();
			}
			else {
				tileTarget = nullptr;
			}
		}
		return true;
	}
	isUpdating = false;
	return false;
}


bool Soldier::MoveUp() {
	if (ChunkHandler::MoveUnit(position, glm::ivec2(position.x, position.y + 1))) {
		position = glm::ivec2(position.x, position.y + 1);
		return true;
	}
	return false;
}
bool Soldier::MoveDown() {
	if (ChunkHandler::MoveUnit(position, glm::ivec2(position.x, position.y - 1))) {
		position = glm::ivec2(position.x, position.y - 1);
		return true;
	}
	return false;
}
bool Soldier::MoveLeft() {
	if (ChunkHandler::MoveUnit(position, glm::ivec2(position.x - 1, position.y))) {
		position = glm::ivec2(position.x - 1, position.y);
		return true;
	}
	return false;
}
bool Soldier::MoveRight() {
	if (ChunkHandler::MoveUnit(position, glm::ivec2(position.x + 1, position.y))) {
		position = glm::ivec2(position.x + 1, position.y);
		return true;
	}
	return false;
}
