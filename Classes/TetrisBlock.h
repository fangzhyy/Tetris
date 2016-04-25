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
    static const int sSquareStruct = 0b1100110000000000;
    static  const int sLStruct = 0b1110100000000000;
    static const int sNLStruct =  0b1110001000000000;
    static const int sTStruct = 0b0100111000000000;
    static  const int sZStruct = 0b1100011000000000;
    static const int sNZStruct = 0b0110110000000000;
    static const int sStickStruct = 0b1111000000000000;
};



#endif