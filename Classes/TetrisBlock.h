#ifndef __TETRISBLOCK_H__
#define __TETRISBLOCK_H__

#include "cocos2d.h"

USING_NS_CC;

class TetrisBlock : public Node
{
private:
	TetrisBlock() : mBlockSprite(nullptr){};
	bool init();
public:
	static TetrisBlock* createBlockByStruct(const byte structNumber, RefPtr<Sprite> unitSprite, float scaleRatio);
	CREATE_FUNC(TetrisBlock);
private:
	byte mStruct;
	void setStruct(byte s){
		mStruct = s;
	}
	void setSpriteByStruct();

private:
	Sprite* mBlockSprite;
};



#endif