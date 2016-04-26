#include "TetrisGameAreaLayer.h"
#include "TetrisBlock.h"

const float TetrisGameAreaLayer::KAreaHRationInVisible = 0.9;
const byte TetrisGameAreaLayer::sSquareStructs[] = { 0xcc, 0xe8, 0xe2, 0xe4, 0xc6, 0x6c, 0xf0 };

bool TetrisGameAreaLayer::init()
{
	LayerColor::initWithColor(Color4B(255, 255, 255, 255));
	auto keyListener = EventListenerKeyboard::create();
	keyListener->setEnabled(true);
	keyListener->onKeyReleased = std::bind(&TetrisGameAreaLayer::onKeyReleased, this, std::placeholders::_1,std::placeholders::_2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
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
	//renderTest();
	return true;
}

void TetrisGameAreaLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		int i = 0;
		i++;

	}
}

void TetrisGameAreaLayer::initBlockRectSprite() {
	if (mBlockUnitSprite.size() > 0)
		return;
    if(mTexCache == nullptr)
        mTexCache = new TextureCache();
    auto tex = mTexCache->addImage("rect.png");
    float miniBlockSize = tex->getContentSize().height;
    float areaWidth = getContentSize().width;
    float desiredBlockWidth = areaWidth / 10.0f;
	mGridSize = desiredBlockWidth;
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
	dropNewBlock();
}

TetrisBlock* TetrisGameAreaLayer::makeCustomBlock()
{
	int randomIndex = RandomHelper::random_int(0, KBlockType);
	auto block = TetrisBlock::createBlockByStruct(sSquareStructs[randomIndex], mBlockUnitSprite.at(randomIndex), mScalRatio);
	return block;
}

void TetrisGameAreaLayer::dropNewBlock()
{
	auto newBlock = makeCustomBlock();
	Size s = newBlock->getContentSize();
	Size layerSize = getContentSize();
	newBlock->setPosition(Vec2(layerSize.width/2, layerSize.height));
	addChild(newBlock);
	auto move = MoveBy::create(1, Vec2(0,-1 * mGridSize));
	newBlock->runAction(move);
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