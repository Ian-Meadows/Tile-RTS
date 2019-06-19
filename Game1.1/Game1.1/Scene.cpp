#include "Scene.h"



Scene::Scene(std::string name)
{
	this->name = name;
}


Scene::~Scene()
{
}

void Scene::Init() {

}
void Scene::Draw() {

}
void Scene::Update() {

}
void Scene::Uninit() {

}

void Scene::AddUIElement(UIElement* element) {
	uiElements->push_back(element);
}

bool Scene::RemoveUIElement(std::string name) {
	for (unsigned int i = 0; i < uiElements->size(); ++i) {
		if ((*uiElements)[i] != nullptr && (*uiElements)[i]->name == name) {
			UIElement* element = (*uiElements)[i];
			uiElements->erase(uiElements->begin() + i);
			delete element;
			return true;
		}
	}
	return false;
}
bool Scene::RemoveUIElement(UIElement* element) {
	for (unsigned int i = 0; i < uiElements->size(); ++i) {
		if ((*uiElements)[i] == element) {
			uiElements->erase(uiElements->begin() + i);
			return true;
		}
	}
	return false;
}


std::vector<UIElement*>* Scene::GetUIElements() {
	return uiElements;
}
