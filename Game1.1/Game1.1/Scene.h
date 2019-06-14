#pragma once
#include <string>

class Scene
{
public:
	Scene(std::string name);
	~Scene();

	//called when scene is set as the current scene
	virtual void Init();
	//use for drawing stuff
	virtual void Draw();
	//use for updating stuff
	virtual void Update();
	//called when scene is no longer the current scene
	virtual void Uninit();

	//the scenes name
	std::string name;

private:

};

