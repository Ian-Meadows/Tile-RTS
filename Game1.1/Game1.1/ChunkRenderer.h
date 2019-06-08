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
	void SetBasicTextureCoordinates();

	unsigned int VAO;
	//0:shape
	//1:position
	//2:unit number
	//3:texCoords
	//4:basicTexCoords
	unsigned int VBO[5];
	unsigned int EBO;

	Chunk* chunk;

	glm::ivec2* positions;

	glm::ivec2* unitNumbers;



};

