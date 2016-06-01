#ifndef __TETRISBLOCK_H__
#define __TETRISBLOCK_H__

#include "cocos2d.h"

USING_NS_CC;

#ifndef byte
typedef unsigned char byte;
#endif

//class TetrisBlockPos
//{
//public:
//	TetrisBlockPos(Vec2 pos, Sprite* sp) : mPos(pos), mSprite(sp), mIndexXInGrid(0), mIndexYInGrid(0){
//
//	}
//	Vec2 mPos;
//	Sprite* mSprite;
//	int mIndexXInGrid;
//	int mIndexYInGrid;
//
//};

class TetrisBlock : public Ref
{
private:
	TetrisBlock() : mStateIndex(0){};
	bool init();
public:
	static TetrisBlock* createBlockByStruct(std::vector<unsigned short> structs, std::pair<int, int> posInGrind, int blockType);
	TetrisBlock* makeShadowBlock();
	void rotate();
	int getType() {
		return mBlockType;
	}
	inline unsigned short getBlockData() {
		return mStructs.at(mStateIndex);
	}
	void moveInX(bool left);
	bool outOfBounds(int xInGrind);
	inline void moveDown() {
		mPosInGrid.second++;
	}
	inline void moveUp() {
		mPosInGrid.second--;

	}
	inline std::pair<int, int> getPosInGrid(){
		return mPosInGrid;
	}
	inline void setPosInGrid(std::pair<int,int> posInGrid) {
		mPosInGrid = posInGrid;
	}
private:
	std::vector<unsigned short> mStructs;
	std::pair<int, int> mPosInGrid;
	void setState(int s) {
		mStateIndex = s;
	}
	void setType(int type){
		mBlockType = type;
	}
	int mStateIndex;
	void setStruct(std::vector<unsigned short> s);
	void setSpriteByStruct();
	int mBlockType;
};



#endif