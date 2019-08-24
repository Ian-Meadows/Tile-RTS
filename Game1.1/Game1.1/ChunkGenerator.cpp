#include "ChunkGenerator.h"
#include <random>




namespace ChunkGenerator {
	void Init() {
		srand(NULL);
	}

	void GenerateChunk(Chunk* chunk) {
		int num = rand() % 4;



		switch (num) {
			case 0:
				chunk->chunkType = TileType::Empty;
				break;
			case 1:
				chunk->chunkType = TileType::Fire;
				break;
			case 2:
				chunk->chunkType = TileType::Water;
				break;
			case 3:
				chunk->chunkType = TileType::Biomass;
				break;
			default:
				chunk->chunkType = TileType::Empty;
				break;
		}
	}

	void Uninit() {

	}
}
