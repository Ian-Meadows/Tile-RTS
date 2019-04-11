#pragma once
#include "Shader.h"

class Chunk;

class ChunkRenderer
{
public:
	ChunkRenderer(Chunk*);
	~ChunkRenderer();

	void Draw();

private:
	void Init();

	void SetPositions();

	void SetUnitInfo(bool);

	unsigned int VAO;
	//0:shape
	//1:position
	//2:unit number
	unsigned int VBO[3];
	unsigned int EBO;

	Chunk* chunk;

	glm::ivec2* positions;

	glm::ivec2* unitNumbers;



};

