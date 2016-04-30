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
	TetrisBlock() : mBlockSprite(nullptr), mStateIndex(0), mBlockLineCount(0), mBlockColCount(0){};
	bool init();
public:
<<<<<<< Updated upstream
	static TetrisBlock* createBlockByStruct(std::vector<unsigned short> structs, RefPtr<Sprite> unitSprite, float scaleRatio);
=======
	static TetrisBlock* createBlockByStruct(const byte structNumber, RefPtr<Sprite> unitSprite, float scaleRatio);
    
	//virtual std::vector<unsigned int> getTopOffsets();
	//virtual std::vector<unsigned int> getBottomOffsets();

>>>>>>> Stashed changes
	CREATE_FUNC(TetrisBlock);
	void rotate();
	int getBlockColCount(){
		return mBlockColCount;
	}
	std::vector<Vec2> getSpriteOffsets();
private:
	std::vector<unsigned short> mStructs;
	int mStateIndex;
	void setStruct(std::vector<unsigned short> s){
		mStructs = s;
	}
	void setSpriteByStruct();
	int mBlockLineCount;
	int mBlockColCount;
private:
<<<<<<< Updated upstream
	Sprite* mBlockSprite;
=======
	cocos2d::Sprite* mBlockSprite;
	unsigned int mBlockWidthForCurrentRes;
    void setStruct(const byte s){ mStruct = s;}
    enum RotateState{
        ERaw = 1,
        ER1,
        ER2,
        ER3
    } mRotateState;
    byte mStruct;
    //static  const int sLStruct = 0xe8;
    //static const int sNLStruct =  0xe2;
    //static const int sTStruct = 0x4e;
    //static  const int sZStruct = 0xc6;
    //static const int sNZStruct = 0x6c;
    //static const int sStickStruct = 0xf0;
>>>>>>> Stashed changes
};



#endif