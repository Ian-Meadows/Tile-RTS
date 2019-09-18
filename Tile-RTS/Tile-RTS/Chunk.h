#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "ChunkHandler.h"
#include "Tile.h"
#include "TextureAtlas.h"

#define CHUNK_SIZE 32
#define UNIT_SIZE 1
/*
draw options
have vao for every chunk always in vram(lot of space)
init when going to draw(might be expensive to do)
*/
//lmao wat? the chunk doesn't even draw itsself anymore.


enum GenerationLevel { None, Semi, Full};

//forward include
class ChunkRenderer;


class Chunk
{
public:
	Chunk(glm::ivec2);
	~Chunk();
	

	glm::ivec2 GetPosition();

	void SemiGeneration();
	void FullGeneration();

	GenerationLevel GetGenerationLevel();

	//returns true if there is a new update to the chunk
	bool CheckForRenderUpdate();

	void Rendered();



	TileType chunkType = TileType::Empty;

	glm::ivec2 GetTileInfo(glm::ivec2 tilePos, TextureAtlas* ta);

	void SetChunkRenderer(ChunkRenderer* cr);

	//Takes local Coords and non null unit(does not check if null). Places unit in position if possible
	bool PlaceUnit(glm::ivec2 position, Unit* unit);

	//Takes local Coords. Returns unit at coords
	Unit* GetUnit(glm::ivec2 position);

	//Takes local Coords. Sets unit to null
	bool ClearUnit(glm::ivec2 position);

private:

	glm::ivec2 position;
	
	GenerationLevel gl = GenerationLevel::None;

	//2D with pointer to object
	Tile*** tiles;

	bool unrenderedUpdate = true;

	ChunkRenderer* cr;

	//TODO:check if this is needed
	bool OutOfRange(glm::ivec2 coords);
};

