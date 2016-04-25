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
	mBlockL = Sprite::create("L.png");
	auto director = Director::getInstance();
	Size visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();
	mBlockL->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - mBlockL->getContentSize().height/2));
	setColor(Color3B(100, 100, 100));
	addChild(mBlockL);
//	mBlockL->runAction(ma);
	return true;
}