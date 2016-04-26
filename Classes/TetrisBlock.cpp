#include "TetrisBlock.h"

bool TetrisBlock::init()
{	
	Node::init();
	return true;
}

TetrisBlock* TetrisBlock::createBlockByStruct(const byte structNumber, RefPtr<Sprite> unitSprite, float scaleRatio)
{	
	TetrisBlock* newBlock = TetrisBlock::create();
	byte mask = 0x80;
	float unitSize = unitSprite->getContentSize().width;
	int maxLine = 0;
	int maxCol = 0;
	for (int i = 1; i < 9; i++) {
		if (mask & structNumber) {
			int line = 1 + i / 4;
			int column = i % 4;
			maxLine = line > maxLine ? line : maxLine;
			maxCol = column > maxCol ? column : maxCol;
			Sprite* newSp = Sprite::createWithSpriteFrame(unitSprite->getSpriteFrame());
			//newSp->setScale(scaleRatio);
			newSp->setAnchorPoint(Vec2(0,0));
			float posX = (column - 1) *  unitSize;
			float posY = -1 * (line - 1) * unitSize;
			newSp->setPosition(Vec2(posX, posY));
			newBlock->addChild(newSp);
		}
		mask = mask >> 1;

	}
	newBlock->setScale(scaleRatio);
	newBlock->setStruct(structNumber);
	newBlock->setAnchorPoint(Vec2(maxLine * unitSize /2, maxCol * unitSize / -2));
	return newBlock;
}
