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
	if (mActiveBlock == nullptr)
		return;
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		mActiveBlock->rotate();
		mShadowBlock->rotate();
		drawAllBlocks();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		mActiveBlock->moveInX(true);
		drawAllBlocks();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		mActiveBlock->moveInX(false);
		drawAllBlocks();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		mAcc = true;
	}

}

void TetrisGameAreaLayer::drawAllBlocks() {
	drawBlock(mActiveBlock, mActiveSprites);
	drawShadowBlock();

}

void TetrisGameAreaLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		mAcc = false;
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
    float desiredBlockWidth = areaWidth / 10.0;
	mGridSize = desiredBlockWidth;
	mScalRatio = desiredBlockWidth / miniBlockSize;
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
	if (mActiveBlock != nullptr) {
		if (blockReachBottom())
			dropNewBlock();
		else{
			mActiveBlock->moveDown();
			drawBlock(mActiveBlock, mActiveSprites);
		}
	}
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
	auto block = TetrisBlock::createBlockByStruct(sV, std::pair<int, int>(0,3), randomIndex);
	return block;
}

void TetrisGameAreaLayer::dropNewBlock()
{
	CC_SAFE_RELEASE(mActiveBlock);
	CC_SAFE_RELEASE(mShadowBlock);
	mActiveBlock = nullptr;
	mShadowBlock = nullptr;
	mActiveSprites.clear();
	for (auto info : mShadowSprites) {
		removeChild(info->ptrSp);
	}
	mShadowSprites.clear();
	auto newBlock = makeCustomBlock();
	mActiveBlock = newBlock;
	drawAllBlocks();
	//dealShadowBlock();
}

void TetrisGameAreaLayer::prepareSprite(int blockType, Vector<RefPtr<UnitInfo> >& sprites){
	if (sprites.size() == 0) {
		for (int i = 0; i < 4; i++) {
			auto newSp = Sprite::createWithSpriteFrame(mBlockUnitSprite.at(blockType)->getSpriteFrame());
			newSp->setAnchorPoint(Vec2::ZERO);
			newSp->setScale(mScalRatio);
			sprites.pushBack(new UnitInfo(0, 0, newSp));
			addChild(newSp);
		}
	}
}

void TetrisGameAreaLayer::drawBlock(TetrisBlock* pBlock, Vector<RefPtr<UnitInfo> >& sprites){
	unsigned short blockStruct = pBlock->getBlockData();
	std::pair<int, int> blockPosInGrind = pBlock->getPosInGrid();
	int blockType = pBlock->getType();
	prepareSprite(blockType, sprites);
	unsigned short mask = 1 << 15;
	int unitIndex = 0;
	for (int i = 0; i < 16; i++) {
		if (blockStruct & mask){
			int line = i / 4;
			int col = i % 4;
			int unitPosX = blockPosInGrind.first + col;
			int unitPosY = blockPosInGrind.second + line;
			auto sp = sprites.at(unitIndex)->ptrSp;
			int drawPosY = KGrindLine - unitPosY - 1;
			sp->setPosition(unitPosX * mGridSize, drawPosY * mGridSize);
			sprites.at(unitIndex)->xInGrid = unitPosX;
			sprites.at(unitIndex)->yInGrid = unitPosY;
			unitIndex++;
		}
		mask = mask >> 1;
		if (unitIndex == sprites.size())
			break;
	}

}

void TetrisGameAreaLayer::drawShadowBlock(){
	int blockType = mActiveBlock->getType();
	prepareSprite(blockType, mShadowSprites);
	for (auto info : mShadowSprites){
		info->ptrSp->setOpacity(80);
	}
	if (mShadowBlock == nullptr){
		mShadowBlock = mActiveBlock->makeShadowBlock();
	}
	int minGridDistance = -1;
	for (auto info : mActiveSprites) {
		int topIndex = getTopGridIndex(info->xInGrid);
		int gridDistance = topIndex - info->yInGrid;
		if (minGridDistance < 0 || gridDistance < minGridDistance) {
			minGridDistance = gridDistance;
		}
	}
	int posY = mActiveBlock->getPosInGrid().second + minGridDistance - 1;
	mShadowBlock->setPosInGrid(std::pair<int, int>(mActiveBlock->getPosInGrid().first, posY));
	drawBlock(mShadowBlock, mShadowSprites);
}

int TetrisGameAreaLayer::getTopGridIndex(int xIndex)
{
	int i = 0;
	for (; i < KGrindLine; i++){
		if (mGridInfo[xIndex][i] != nullptr)
			return i;
	}
	return i;
}

bool TetrisGameAreaLayer::blockReachBottom()
{
	bool dead = false;
	for (auto info : mActiveSprites){
		if (info->yInGrid == KGrindLine - 1 || mGridInfo[info->xInGrid][info->yInGrid + 1] != nullptr){
			dead = true;
			break;
		}
	}
	if (dead) {
		for (auto info : mActiveSprites){
			int xx = info->xInGrid;
			int yy = info->yInGrid;
			mGridInfo[info->xInGrid][info->yInGrid] = info->ptrSp;
		}
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


