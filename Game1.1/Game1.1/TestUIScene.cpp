#include "TestUIScene.h"
#include <iostream>
#include "TestButton.h"
#include "Text.h"



TestUIScene::TestUIScene() : Scene("UITest")
{
	
}


TestUIScene::~TestUIScene()
{
}

void TestUIScene::Init() {
	AddUIElement(new TestButton());
	AddUIElement(new Text());
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