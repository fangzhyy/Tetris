#ifndef __TETRISBLOCK_H__
#define __TETRISBLOCK_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisBlock : public Node
{
private:
	TetrisBlock() : mBlockWidthForCurrentRes(0), mBlockSprite(nullptr){};
	bool init();
public:
	static TetrisBlock* createBlockByStruct(const byte structNumber, RefPtr<Sprite> unitSprite, float scaleRatio);
	//virtual std::vector<unsigned int> getTopOffsets();
	//virtual std::vector<unsigned int> getBottomOffsets();

	CREATE_FUNC(TetrisBlock);
private:
	cocos2d::Sprite* mBlockSprite;
	unsigned int mBlockWidthForCurrentRes;
    //static  const int sLStruct = 0xe8;
    //static const int sNLStruct =  0xe2;
    //static const int sTStruct = 0x4e;
    //static  const int sZStruct = 0xc6;
    //static const int sNZStruct = 0x6c;
    //static const int sStickStruct = 0xf0;
};



#endif