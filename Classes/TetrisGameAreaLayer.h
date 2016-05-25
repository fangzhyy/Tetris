#ifndef __TETRISGAMEAREALAYER_H__
#define __TETRISGAMEAREALAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisBlock;

#ifndef byte
typedef unsigned char byte;
#endif

class TetrisGameAreaLayer : public LayerColor {
private:
	bool init();
	static const int KHBorder = 5;
	static const int KWBorder = 5;
	static const int KBlockType = 7;
	static const float KAreaHRationInVisible;
	static const int mGrindCol = 10;
    Sprite* mGridInfo[mGrindCol][mGrindCol * 2 + 5];
    Sprite* mBottomBlocks;
	TetrisBlock* makeCustomBlock();
	void initBlockRectSprite();
    RefPtr<TextureCache> mTexCache;
	Vector<RefPtr<Sprite> > mBlockUnitSprite;
	static const unsigned short sSquareStructs[KBlockType][4];
	float mScalRatio;
	float mGridSize;
	void renderTest();
	void dropNewBlock();
	void onBlockAcc();
	int getTopGridIndex(int xIndex);
	Vec2 getBlockEndPos();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event* unused_event);
	bool blockReachBottom();
	TetrisBlock* mActiveBlock;
	TetrisBlock* mShadowBlock;
	void onBlockUpdate(float delta);
    void updateBottomBlocks();
	void dealShadowBlock();
	virtual void update(float dt) override;
    RenderTexture* mBottomTex;
	bool mAcc;
	float mNormalSpeed;
	float mAccSpeed;
	float mUpdateDt;
public:
	TetrisGameAreaLayer() : mActiveBlock(nullptr), mNormalSpeed(0.5), mAccSpeed(0.1)
							,mAcc(false), mShadowBlock(nullptr), mUpdateDt(0){
		memset(mGridInfo, 0, sizeof(mGridInfo));
	};
	CREATE_FUNC(TetrisGameAreaLayer);
};

#endif