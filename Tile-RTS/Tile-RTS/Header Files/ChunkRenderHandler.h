#pragma once
#include "ChunkRenderer.h"
#include "Shader.h"


namespace ChunkRenderHandler {
	void Init();
	void Draw();
	void UnInit();

	Shader* GetShader();
}



