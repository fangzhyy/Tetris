#ifndef __TETRISGAMEAREALAYER_H__
#define __TETRISGAMEAREALAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisGameAreaLayer : public LayerColor {
private:
	bool init();
	static const int KHBorder = 5;
	static const int KWBorder = 5;
	static const int KBlockType = 7;
	static const float KAreaHRationInVisible;
    void makeCustomBlock();
	void initBlockRectSprite();
    RefPtr<TextureCache> mTexCache;
	Vector<RefPtr<Sprite> > mBlockUnitSprite;
	static const byte sSquareStructs[];
	float mScalRatio;
	void renderTest();
public:
	CREATE_FUNC(TetrisGameAreaLayer);
};

#endif