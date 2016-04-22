#include "TetrisGameAreaLayer.h"

const float TetrisGameAreaLayer::KAreaHRationInVisible = 0.9;

bool TetrisGameAreaLayer::init()
{
	LayerColor::initWithColor(Color4B(100, 100, 100, 255));
	auto dtor = Director::getInstance();
	Size  vSize = dtor->getVisibleSize();
	Vec2 org = dtor->getVisibleOrigin();
	//left bottom
	Vec2 vlb(org.x + KWBorder, org.y + KHBorder);
	int areaHeight = vSize.height * KAreaHRationInVisible;
	setContentSize(Size(areaHeight/2 - 2 * KWBorder, areaHeight - 2 * KHBorder));
	setAnchorPoint(Vec2(0 ,0));
	setPosition(vlb);

	return true;
}