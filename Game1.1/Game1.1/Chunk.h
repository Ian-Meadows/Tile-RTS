#pragma once
#include <glm/glm.hpp>
class Chunk
{
public:
	Chunk(glm::vec2);
	~Chunk();

private:
	glm::vec2 position;

};

