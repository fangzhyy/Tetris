#include "TetrisGameAreaLayer.h"
#include "TetrisBlock.h"

const float TetrisGameAreaLayer::KAreaHRationInVisible = 0.9;
const byte TetrisGameAreaLayer::sSquareStructs[] = { 0xcc, 0xe8, 0xe2, 0x4e, 0xc6, 0x6c, 0xf0 };

bool TetrisGameAreaLayer::init()
{
	LayerColor::initWithColor(Color4B(255, 255, 255, 255));
	auto dtor = Director::getInstance();
	Size  vSize = dtor->getVisibleSize();
	Vec2 org = dtor->getVisibleOrigin();
	//left bottom
	Vec2 vlb(org.x + KWBorder, org.y + KHBorder);
	int areaHeight = vSize.height * KAreaHRationInVisible;
	setContentSize(Size(areaHeight/2 - 2 * KWBorder, areaHeight - 2 * KHBorder));
	setAnchorPoint(Vec2(0 ,0));
	setPosition(vlb);
	initBlockRectSprite();
	renderTest();
	return true;
}

void TetrisGameAreaLayer::initBlockRectSprite() {
	if (mBlockUnitSprite.size() > 0)
		return;
    if(mTexCache == nullptr)
        mTexCache = new TextureCache();
    auto tex = mTexCache->addImage("rect.png");
    float miniBlockSize = tex->getContentSize().height;
	float xx = tex->getContentSize().width;
    float areaWidth = getContentSize().width;
    float desiredBlockWidth = areaWidth / 10.0f;
	mScalRatio = desiredBlockWidth / miniBlockSize;
    Rect r;
    int testPos = 0;
	r.setRect(miniBlockSize, 0, miniBlockSize, miniBlockSize);
	auto testNode = Node::create();
	testNode->setPosition(200, 200);
	//addChild(testNode);
	
	for (int i = 0; i < KBlockType; i++) {
        //加载材质
		Sprite* miniSprite = Sprite::createWithTexture(tex, r);
		//miniSprite->
		r.setRect(r.origin.x + miniBlockSize, r.origin.y, miniBlockSize, miniBlockSize);
		RefPtr<Sprite> ptr = RefPtr<Sprite>(miniSprite);
		mBlockUnitSprite.pushBack(ptr);
		//测试加载的材质
  //      miniSprite->setAnchorPoint(Vec2(0,0));
  //      miniSprite->setPosition(testPos , 0);
  //     testPos += 50;
		//testNode->addChild(miniSprite);
    }
	//testNode->setRotation(30);
	//makeCustomBlock();
}

void TetrisGameAreaLayer::makeCustomBlock()
{
	auto block = TetrisBlock::createBlockByStruct(sSquareStructs[3], mBlockUnitSprite.at(3), mScalRatio);
	block->setPosition(150, 150);

	addChild(block);
}

void TetrisGameAreaLayer::renderTest()
{
	auto rt = RenderTexture::create(getContentSize().width, getContentSize().height);
	rt->begin();
	Vec2 pos(50,300);
	for (auto sp : mBlockUnitSprite) {
		sp->setPosition(pos);
		sp->visit();
		pos.x = pos.x + 50;
	}
	rt->end();
	auto newSp = Sprite::createWithTexture(rt->getSprite()->getTexture());
	newSp->setAnchorPoint(Vec2(0,0));
	addChild(newSp);
}