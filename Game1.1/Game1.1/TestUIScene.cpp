#include "TestUIScene.h"
#include <iostream>
#include "Button.h"



TestUIScene::TestUIScene() : Scene("UITest")
{
	
}


TestUIScene::~TestUIScene()
{
}

void TestUIScene::Init() {
	AddUIElement(new Button());
	test = new TestRenderer();
}

void TestUIScene::Draw() {
	test->Draw();
}

void TestUIScene::Update() {
	test->Update();
}

void TestUIScene::Uninit() {
	delete test;
}