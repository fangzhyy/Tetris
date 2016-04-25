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
    makeAllKindBlock();
	return true;
}

void TetrisGameAreaLayer::makeAllKindBlock() {
    if(mTexCache == nullptr)
        mTexCache = new TextureCache();
    auto tex = mTexCache->addImage("rect.png");
    float miniBlockSize = tex->getContentSize().height;
    float areaWidth = getContentSize().width;
    float desiredBlockWidth = areaWidth / 10.0f;
    float ratio = desiredBlockWidth/miniBlockSize;
    Rect r;
    int testPos = getPosition().x;
    r.setRect(0, 0, miniBlockSize, miniBlockSize);
    for(int i = 1; i < 9; i++) {
        //加载材质
        auto miniSprite = Sprite::createWithTexture(tex, r);
        r.setRect(r.origin.x + miniBlockSize, r.origin.y, miniBlockSize, miniBlockSize);
        miniSprite->setScale(ratio);
        miniSprite->setAnchorPoint(Vec2(0,0));
        miniSprite->setPosition(testPos , 80);
        testPos += 50;
        addChild(miniSprite);
        
    }
    
}