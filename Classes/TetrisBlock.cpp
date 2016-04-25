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
	for (int i = 1; i < 9; i++) {
		if (mask & structNumber) {
			int line = 1 + i / 4;
			int column = i % 4;
			Sprite* newSp = Sprite::createWithSpriteFrame(unitSprite->getSpriteFrame());
			//newSp->setScale(scaleRatio);
			newSp->setAnchorPoint(Vec2(0,0));
			float posX = -1 *(column - 1) *  unitSize;
			float posY = -1 * (line - 1) * unitSize;
			newSp->setPosition(Vec2(posX, posY));
			newBlock->addChild(newSp);
		}
		mask = mask >> 1;

	}
	newBlock->setScale(scaleRatio);
	return newBlock;
}