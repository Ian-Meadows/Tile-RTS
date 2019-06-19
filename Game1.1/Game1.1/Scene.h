#pragma once
#include <string>
#include <vector>

#include "UIElement.h"

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

	//adds the element
	virtual void AddUIElement(UIElement*) final;
	//removes and deletes the element
	virtual bool RemoveUIElement(std::string) final;
	//only removes element
	virtual bool RemoveUIElement(UIElement*) final;


	virtual std::vector<UIElement*>* GetUIElements() final;

private:
	std::vector<UIElement*>* uiElements = nullptr;
};

