#pragma once
#include <string>

class Scene
{
public:
	Scene(std::string name);
	~Scene();

	void Init();
	void Draw();
	void Update();
	void Uninit();

	std::string name;

private:

};

