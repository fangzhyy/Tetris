#include "TetrisBlock.h"
#include "TetrisGameAreaLayer.h"

bool TetrisBlock::init()
{
	return true;
}


TetrisBlock* TetrisBlock::createBlockByStruct(std::vector<unsigned short> structs, std::pair<int, int> posInGrind, int blockType) {
	auto newBlock = new TetrisBlock();
	newBlock->setStruct(structs);
	newBlock->setType(blockType);
	newBlock->mPosInGrid = posInGrind;
	return newBlock;
}

void TetrisBlock::setStruct(std::vector<unsigned short> s){
	mStructs = s;
}

TetrisBlock* TetrisBlock::makeShadowBlock(){
	TetrisBlock* newBlock = createBlockByStruct(mStructs, std::pair<int, int>(0, 0), mBlockType);
	newBlock->setState(mStateIndex);
	return newBlock;
}

bool TetrisBlock::outOfBounds(int xInGrind) {
	unsigned short mask = 1 << 15;
	int foundCount = 0;
	for (int i = 0; i < 16; i++) {
		if (mStructs.at(mStateIndex) & mask){
			int col = i % 4;
			int unitPosX = xInGrind + col;
			if (unitPosX < 0 || unitPosX >= TetrisGameAreaLayer::KGrindCol)
				return true;
			foundCount++;
		}
		mask = mask >> 1;
		if (foundCount == 4)
			break;
	}
	return false;
}

void TetrisBlock::moveInX(bool left){
	int aftMoveX = left ? mPosInGrid.first - 1 : mPosInGrid.first + 1;
	if (outOfBounds(aftMoveX))
		return;
	mPosInGrid.first = aftMoveX;
}

//void TetrisBlock::setSpriteByStruct()
//{
//	Vector<Node*> c = getChildren();
//	unsigned short mask = 0x01;
//	float unitSize = c.at(0)->getContentSize().width;
//	int maxLine = 0;
//	int maxCol = 0;
//	int baseLine = -1;
//	int childrenIndex = 0;
//	for (int i = 0; i < 16; i++) {
//		if (mask & mStructs[mStateIndex]) {
//			int line = 3 - i / 4;
//			if (baseLine < 0)
//				baseLine = line;
//			int column = 3 - i % 4;
//			maxLine = line > maxLine ? line : maxLine;
//			maxCol = column > maxCol ? column : maxCol;
//			float posX = column  *  unitSize;
//			float posY = (baseLine - line) * unitSize;
//			c.at(childrenIndex)->setPosition(Vec2(posX, posY));
//			if (++childrenIndex == c.size())
//				break;
//		}
//		mask = mask << 1;
//	}
//	mBlockLineCount = maxLine + 1;
//	mBlockColCount = maxCol + 1;
//}

void TetrisBlock::rotate()
{
	int maxIndex = mStructs.size() - 1;
	if (mStateIndex < maxIndex) {
		mStateIndex++;
		if (mStructs.at(mStateIndex) == 0)
			mStateIndex = 0;
	}
	else
		mStateIndex = 0;
	while (outOfBounds(mPosInGrid.first)){
		mPosInGrid.first--;
	}
}


