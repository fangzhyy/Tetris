#ifndef __TETRISGAMEAREALAYER_H__
#define __TETRISGAMEAREALAYER_H__

#include "cocos2d.h"

USING_NS_CC;

<<<<<<< Updated upstream
class TetrisBlock;
=======
#ifndef byte
typedef unsigned char byte;
#endif
>>>>>>> Stashed changes

class TetrisGameAreaLayer : public LayerColor {
private:
	bool init();
	static const int KHBorder = 5;
	static const int KWBorder = 5;
	static const int KBlockType = 7;
	static const float KAreaHRationInVisible;
	static const int mGrindCol = 10;
	byte mGridInfo[mGrindCol][mGrindCol * 2];
	TetrisBlock* makeCustomBlock();
	void initBlockRectSprite();
    RefPtr<TextureCache> mTexCache;
	Vector<RefPtr<Sprite> > mBlockUnitSprite;
<<<<<<< Updated upstream
	static const unsigned short sSquareStructs[7][4];
=======
    static const byte sSquareStructs[];
>>>>>>> Stashed changes
	float mScalRatio;
	int mGridSize;
	void renderTest();
	void dropNewBlock();
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);
	bool blockReachBottom();
	TetrisBlock* mActiveBlock;
	void onBlockUpdate(float delta);
	
public:
	TetrisGameAreaLayer() : mActiveBlock(nullptr){
		memset(mGridInfo, 0, sizeof(mGrindCol));
	};
	CREATE_FUNC(TetrisGameAreaLayer);
};

#endif