#pragma once
#include "Shader.h"

namespace UIHandler {
	void Init();
	void Draw();
	void Uninit();

	Shader* GetTextShader();
	Shader* GetShapeShader();
}

