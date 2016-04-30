#include "TetrisBlock.h"

bool TetrisBlock::init()
{	
	Node::init();
	return true;
}

<<<<<<< Updated upstream
TetrisBlock* TetrisBlock::createBlockByStruct(std::vector<unsigned short> structs, RefPtr<Sprite> unitSprite, float scaleRatio)
{	
=======
TetrisBlock* TetrisBlock::createBlockByStruct(const byte structNumber, RefPtr<Sprite> unitSprite, float scaleRatio)
{
>>>>>>> Stashed changes
	TetrisBlock* newBlock = TetrisBlock::create();
	unsigned short mask = 0x01;
	float unitSize = unitSprite->getContentSize().width;
	for (int i = 0; i < 4; i++) {
		auto newSp = Sprite::createWithSpriteFrame(unitSprite->getSpriteFrame());
		newSp->setAnchorPoint(Vec2(0,0));
		newBlock->addChild(newSp);
	}
	newBlock->setStruct(structs);
	newBlock->setSpriteByStruct();
	newBlock->setScale(scaleRatio);
<<<<<<< Updated upstream
	newBlock->setAnchorPoint(Vec2(0, 0));
=======
    newBlock->setStruct(structNumber);
>>>>>>> Stashed changes
	return newBlock;
}

void TetrisBlock::setSpriteByStruct()
{
	Vector<Node*> c = getChildren();
	unsigned short mask = 0x01;
	float unitSize = c.at(0)->getContentSize().width;
	int maxLine = 0;
	int maxCol = 0;
	int baseLine = -1;
	int childrenIndex = 0;
	for (int i = 0; i < 16; i++) {
		if (mask & mStructs[mStateIndex]) {
			int line = 3 - i / 4;
			if (baseLine < 0)
				baseLine = line;
			int column = 3 - i % 4;
			maxLine = line > maxLine ? line : maxLine;
			maxCol = column > maxCol ? column : maxCol;
			float posX = column  *  unitSize;
			float posY = (baseLine - line) * unitSize;
			c.at(childrenIndex)->setPosition(Vec2(posX, posY));
			if (++childrenIndex == c.size())
				break;
		}
		mask = mask << 1;
	}
	mBlockLineCount = maxLine + 1;
	mBlockColCount = maxCol + 1;
}

void TetrisBlock::rotate()
{
	int maxIndex = mStructs.size() - 1;
	if (mStateIndex < maxIndex) {
		mStateIndex++;
	}
	else
		mStateIndex = 0;
	setSpriteByStruct();
}

std::vector<Vec2> TetrisBlock::getSpriteOffsets()
{
	Vector<Node*> ch = getChildren();
	std::vector<Vec2> offsetV;
	for (Node* c : ch){
		int posY = c->getPositionY + c->getContentSize().width * getScale();
		int posX = c->getPositionX + c->getContentSize().width * getScale();
		offsetV.push_back(Vec2(posX, posY));
	}
	return offsetV;
}