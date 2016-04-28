#ifndef __TETRISGAMEAREALAYER_H__
#define __TETRISGAMEAREALAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisBlock;

class TetrisGameAreaLayer : public LayerColor {
private:
	bool init();
	static const int KHBorder = 5;
	static const int KWBorder = 5;
	static const int KBlockType = 7;
	static const float KAreaHRationInVisible;
	static const int mGrindCol = 10;
	int mTopOffsets[mGrindCol];
	TetrisBlock* makeCustomBlock();
	void initBlockRectSprite();
    RefPtr<TextureCache> mTexCache;
	Vector<RefPtr<Sprite> > mBlockUnitSprite;
	static const unsigned short sSquareStructs[7][4];
	float mScalRatio;
	float mGridSize;
	void renderTest();
	void dropNewBlock();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	bool blockReachBottom();
	TetrisBlock* mActiveBlock;
	void onBlockUpdate(float delta);
	
public:
	TetrisGameAreaLayer() : mActiveBlock(nullptr){
		memset(mTopOffsets, 0, sizeof(mTopOffsets));
	};
	CREATE_FUNC(TetrisGameAreaLayer);
};

#endif