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
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	bool blockReachBottom();
	TetrisBlock* mActiveBlock;
	void onBlockUpdate(float delta);
    void updateBottomBlocks();
    RenderTexture* mBottomTex;
public:
	TetrisGameAreaLayer() : mActiveBlock(nullptr), mBottomTex(nullptr){
		memset(mGridInfo, 0, sizeof(mGridInfo));
	};
	CREATE_FUNC(TetrisGameAreaLayer);
};

#endif