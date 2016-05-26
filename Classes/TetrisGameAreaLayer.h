#ifndef __TETRISGAMEAREALAYER_H__
#define __TETRISGAMEAREALAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisBlock;

#ifndef byte
typedef unsigned char byte;
#endif

class UnitInfo : public Ref {
public:
	UnitInfo(int x, int y, Sprite* sp) : xInGrid(x), yInGrid(y), ptrSp(sp){};
	int xInGrid;
	int yInGrid;
	Sprite* ptrSp;
};

class TetrisGameAreaLayer : public LayerColor {
public:
	static const int KGrindCol = 10;
private:
	bool init();
	TetrisBlock* makeCustomBlock();
	void initBlockRectSprite();
    RefPtr<TextureCache> mTexCache;
	Vector<RefPtr<Sprite> > mBlockUnitSprite;
	void dropNewBlock();
	void drawBlock(TetrisBlock* pBlock, Vector<RefPtr<UnitInfo> >& sprites);
	void drawAllBlocks();
	void onBlockAcc();
	int getTopGridIndex(int xIndex);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event* unused_event);
	bool blockReachBottom();
    void updateBottomBlocks();
	void drawShadowBlock();
	void prepareSprite(int blockType, Vector<RefPtr<UnitInfo> >& sprites);
	virtual void update(float dt) override;
private:
	TetrisBlock* mActiveBlock;
	TetrisBlock* mShadowBlock;
	bool mAcc;
	float mNormalSpeed;
	float mAccSpeed;
	float mUpdateDt;
	float mScalRatio;
	float mGridSize;
	Vector<RefPtr<UnitInfo> > mActiveSprites;
	Vector<RefPtr<UnitInfo> > mShadowSprites;
	static const int KHBorder = 5;
	static const int KWBorder = 5;
	static const int KBlockType = 7;
	static const float KAreaHRationInVisible;
	static const int KGrindLine = 24;
	static const unsigned short sSquareStructs[KBlockType][4];
	RefPtr<Sprite> mGridInfo[KGrindCol][KGrindLine];
public:
	TetrisGameAreaLayer() : mActiveBlock(nullptr), mNormalSpeed(0.5), mAccSpeed(0.1)
							,mAcc(false), mShadowBlock(nullptr), mUpdateDt(0){
	};
	CREATE_FUNC(TetrisGameAreaLayer);
};

#endif