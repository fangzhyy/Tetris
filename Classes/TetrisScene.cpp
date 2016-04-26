#include "TetrisScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TetrisGameAreaLayer.h"

Scene* TetrisScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TetrisScene::create();
	auto gameArealayer = TetrisGameAreaLayer::create();
	// add layer as a child to scene
	scene->addChild(layer);
	layer->addChild(gameArealayer);
	// return the scene
	return scene;
}



bool TetrisScene::init() {
	
	return true;
}