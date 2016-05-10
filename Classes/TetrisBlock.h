#ifndef __TETRISBLOCK_H__
#define __TETRISBLOCK_H__

#include "cocos2d.h"

USING_NS_CC;

#ifndef byte
typedef unsigned char byte;
#endif

class TetrisBlock : public Node
{
private:
	TetrisBlock() : mStateIndex(0), mBlockLineCount(0), mBlockColCount(0){};
	bool init();
public:

	static TetrisBlock* createBlockByStruct(std::vector<unsigned short> structs, RefPtr<Sprite> unitSprite, float scaleRatio);
	CREATE_FUNC(TetrisBlock);
	void rotate();
	int getBlockColCount(){
		return mBlockColCount;
	}
	std::vector<Vec2> getSpriteOffsets();
    void visitSprite();
private:
	std::vector<unsigned short> mStructs;
	int mStateIndex;
	void setStruct(std::vector<unsigned short> s){
		mStructs = s;
	}
	void setSpriteByStruct();
	int mBlockLineCount;
	int mBlockColCount;
};



#endif