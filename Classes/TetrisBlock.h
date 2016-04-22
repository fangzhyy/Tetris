#ifndef __TETRISBLOCK_H__
#define __TETRISBLOCK_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisBlock : public cocos2d::Ref
{
private:
	TetrisBlock() : mBlockWidthForCurrentRes(0), mBlockSprite(nullptr){};
	bool init();
public:
	static TetrisBlock* createRandomBlock();
	virtual std::vector<unsigned int> getTopOffsets();
	virtual std::vector<unsigned int> getBottomOffsets();
private:
	cocos2d::Sprite* mBlockSprite;
	unsigned int mBlockWidthForCurrentRes;
};



#endif