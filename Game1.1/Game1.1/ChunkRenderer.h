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
	void SetTextureCoordinates();

	unsigned int VAO;
	//0:shape
	//1:position
	//2:unit number
	//3:texCoords
	unsigned int VBO[4];
	unsigned int EBO;
	unsigned int texture;

	Chunk* chunk;

	glm::ivec2* positions;

	glm::ivec2* unitNumbers;



};

