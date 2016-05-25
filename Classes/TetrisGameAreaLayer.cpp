#include <vector>
#include "TetrisGameAreaLayer.h"
#include "TetrisBlock.h"


const float TetrisGameAreaLayer::KAreaHRationInVisible = 0.9;
const unsigned short TetrisGameAreaLayer::sSquareStructs[7][4] = {
	{ 0xcc00, 0, 0, 0 }
	, { 0xe800, 0xc440, 0x2e00, 0x88c0 }
	, { 0xe200, 0x44c0, 0x8e00, 0xc880 }
	, { 0xe400, 0x4c40, 0x4e00, 0x8c80 }
	, { 0xc600, 0x4c8, 0, 0 }
	, {0x6c00, 0x8c40, 0, 0 }
	, { 0xf000, 0x8888, 0, 0}
};


bool TetrisGameAreaLayer::init()
{
	LayerColor::initWithColor(Color4B(255, 255, 255, 255));
	auto keyListener = EventListenerKeyboard::create();
	keyListener->setEnabled(true);
	keyListener->onKeyReleased = std::bind(&TetrisGameAreaLayer::onKeyReleased, this, std::placeholders::_1,std::placeholders::_2);
	keyListener->onKeyPressed = std::bind(&TetrisGameAreaLayer::onKeyDown, this, std::placeholders::_1, std::placeholders::_2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	auto dtor = Director::getInstance();
	Size  vSize = dtor->getVisibleSize();
	Vec2 org = dtor->getVisibleOrigin();
	//left bottom
	Vec2 vlb(org.x + KWBorder, org.y + KHBorder);
	int areaHeight = vSize.height * KAreaHRationInVisible;
	setContentSize(Size(areaHeight / 2 - 2 * KWBorder, areaHeight - 4 * KWBorder));
	setAnchorPoint(Vec2(0 ,0));
	setPosition(vlb);
	initBlockRectSprite();
	//schedule(schedule_selector(TetrisGameAreaLayer::onBlockUpdate), 0.0);
	scheduleUpdate();
	return true;
}

void TetrisGameAreaLayer::onKeyDown(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		if (mActiveBlock != nullptr){
			mActiveBlock->rotate();
		}
		float xendPos = mActiveBlock->getBlockColCount() * mGridSize + mActiveBlock->getPositionX();
		while (xendPos > getContentSize().width) {
			mActiveBlock->setPosition(mActiveBlock->getPositionX() - mGridSize, mActiveBlock->getPositionY());
			xendPos = mActiveBlock->getBlockColCount() * mGridSize + mActiveBlock->getPositionX();
		}
		dealShadowBlock();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		if (mActiveBlock->getPositionX() >= mGridSize)
			mActiveBlock->setPosition(mActiveBlock->getPositionX() - mGridSize, mActiveBlock->getPositionY());
			dealShadowBlock();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		float xendPos = mActiveBlock->getBlockColCount() * mGridSize + mActiveBlock->getPositionX();
		if (xendPos + mGridSize <= getContentSize().width + 1.0)
			mActiveBlock->setPosition(mActiveBlock->getPositionX() + mGridSize, mActiveBlock->getPositionY());
		dealShadowBlock();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		mAcc = true;
	}

}

void TetrisGameAreaLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		mAcc = false;
	}
}

void TetrisGameAreaLayer::onBlockUpdate(float delta)
{
	if (blockReachBottom())
		dropNewBlock();
	else
		mActiveBlock->setPosition(mActiveBlock->getPositionX(), mActiveBlock->getPositionY() - mGridSize);	
}

void TetrisGameAreaLayer::initBlockRectSprite() {
	if (mBlockUnitSprite.size() > 0)
		return;
    if(mTexCache == nullptr)
        mTexCache = new TextureCache();
    auto tex = mTexCache->addImage("rect.png");
    float miniBlockSize = tex->getContentSize().height;
    float areaWidth = getContentSize().width;
    float desiredBlockWidth = areaWidth / 10.0;
	mGridSize = desiredBlockWidth;
	mScalRatio = desiredBlockWidth / miniBlockSize;
	//auto dir = Director::getInstance();
    //dir->setContentScaleFactor(mScalRatio);
    Rect r;
	r.setRect(miniBlockSize, 0, miniBlockSize, miniBlockSize);
	for (int i = 0; i < KBlockType; i++) {
        //加载材质
		RefPtr<Sprite> ptr = Sprite::createWithTexture(tex, r);
		r.setRect(r.origin.x + miniBlockSize, r.origin.y, miniBlockSize, miniBlockSize);
		mBlockUnitSprite.pushBack(ptr);
	}
	dropNewBlock();
}

void TetrisGameAreaLayer::onBlockAcc()
{
	

}

void TetrisGameAreaLayer::update(float dt)
{
	if (mAcc){
		mUpdateDt = 0;
		return;
	}
	mUpdateDt += dt;
	if (mUpdateDt < mNormalSpeed)
		return;
	mUpdateDt = 0;
	if (blockReachBottom())
		dropNewBlock();
	else
		mActiveBlock->setPosition(mActiveBlock->getPositionX(), mActiveBlock->getPositionY() - mGridSize);

}

TetrisBlock* TetrisGameAreaLayer::makeCustomBlock()
{
	int randomIndex = RandomHelper::random_int(0, KBlockType - 1);
	std::vector<unsigned short> sV;
	for (int i = 0; i < sizeof(sSquareStructs[randomIndex]) / sizeof(unsigned short); i++) {
		if (sSquareStructs[randomIndex][i] != 0) {
			sV.push_back(sSquareStructs[randomIndex][i]);
		}
		else
			break;
	}
	
	auto block = TetrisBlock::createBlockByStruct(sV, mBlockUnitSprite.at(randomIndex), mScalRatio);
	return block;
}

void TetrisGameAreaLayer::dropNewBlock()
{
	auto newBlock = makeCustomBlock();
	Size s = newBlock->getContentSize();
	Size layerSize = getContentSize();
	newBlock->setPosition(Vec2(0, layerSize.height));
	addChild(newBlock);
	mActiveBlock = newBlock;
	dealShadowBlock();
}

void TetrisGameAreaLayer::dealShadowBlock(){
	if (mShadowBlock == nullptr)
		mShadowBlock = mActiveBlock->createShadowBlock();
	else
		removeChild(mShadowBlock);
	mShadowBlock = mActiveBlock->createShadowBlock();
	Vec2 endPos = getBlockEndPos();
	mShadowBlock->setPosition(endPos);
	addChild(mShadowBlock);
}

Vec2 TetrisGameAreaLayer::getBlockEndPos()
{
	int blockPosY = mActiveBlock->getPositionY();
	int blockPosX = mActiveBlock->getPositionX();
	std::vector<TetrisBlockPos> spritPos = mActiveBlock->getSpriteOffsets();
	int minGridDistance = -1;
	for (TetrisBlockPos pos : spritPos) {
		int indexInGridX = (blockPosX + pos.mPos.x) / mGridSize;
		int indexInGridY = (blockPosY + pos.mPos.y) / mGridSize;
		int topIndex = getTopGridIndex(indexInGridX);
		//topIndex = topIndex < 0 ? 0 : topIndex;
		int gridDistance =  indexInGridY - topIndex;
		if (minGridDistance < 0 || gridDistance < minGridDistance)
			minGridDistance = gridDistance;
	}
	float posX = mActiveBlock->getPositionX();
	float posY = mActiveBlock->getPositionY() - (minGridDistance - 1) * mGridSize;
	return Vec2(posX, posY);
}

int TetrisGameAreaLayer::getTopGridIndex(int xIndex)
{
	for (int i = mGrindCol * 2 - 1; i >= 0; i--) {
		if (mGridInfo[xIndex][i] != 0)
			return i;
	}
	return -1;
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

bool TetrisGameAreaLayer::blockReachBottom()
{
    bool dead = false;
    int blockPosY = mActiveBlock->getPositionY();
    int blockPosX = mActiveBlock->getPositionX();
	std::vector<TetrisBlockPos> spritPos = mActiveBlock->getSpriteOffsets();
	for (TetrisBlockPos& v : spritPos) {
		v.mIndexXInGrid = (blockPosX + v.mPos.x) / mGridSize;
        v.mIndexYInGrid = (blockPosY + v.mPos.y)/mGridSize;
		if (v.mIndexYInGrid == 0 || mGridInfo[v.mIndexXInGrid][v.mIndexYInGrid - 1] != 0)
            dead = true;
    }
    if(dead) {
		for (TetrisBlockPos info : spritPos) {
			Sprite* sp = Sprite::createWithSpriteFrame(info.mSprite->getSpriteFrame());
			addChild(sp);
			sp->setAnchorPoint(Vec2::ZERO);
			sp->setContentSize(info.mSprite->getContentSize() * mScalRatio);
			sp->setScale(mScalRatio);
			int x = info.mSprite->getPositionX();
			sp->setPosition(mActiveBlock->getPositionX() + info.mSprite->getPositionX() * mScalRatio
				, mActiveBlock->getPositionY() + info.mSprite->getPositionY() * mScalRatio);
			mGridInfo[info.mIndexXInGrid][info.mIndexYInGrid] = sp;
		}
		removeChild(mActiveBlock);
    }
    return dead;
}

void TetrisGameAreaLayer::updateBottomBlocks() {
    
  /*  auto rt = RenderTexture::create(getContentSize().width, getContentSize().height);
    rt->retain();
    rt->beginWithClear(0, 255, 255, 255);
    if(mBottomBlocks) {
        mBottomBlocks->visit();
    }
    if(mActiveBlock)
       mActiveBlock->visitSprite();

    rt->end();
    if(mBottomBlocks) {
        removeChild(mBottomBlocks);
        mBottomBlocks = nullptr;
    }
    if(mActiveBlock) {
        removeChild(mActiveBlock);
        mActiveBlock = nullptr;
    }
    mBottomBlocks = Sprite::createWithTexture(rt->getSprite()->getTexture());

    mBottomBlocks->setPosition(mBottomBlocks->getContentSize().width/2, mBottomBlocks->getContentSize().height/2);
    mBottomBlocks->setFlippedY(true);
    addChild(mBottomBlocks);*/
    
}


