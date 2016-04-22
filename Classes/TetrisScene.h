#ifndef __TETRISSCENE_H__
#define __TETRISSCENE_H__


#include "cocos2d.h"

USING_NS_CC;

class TetrisScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(TetrisScene);

private:
	Sprite* mBlockSquare;
	Sprite* mBlockZ;
	Sprite* mBlockRZ;
	Sprite* mBlockL;
	Sprite* mBlockRL;
	Sprite* mBlockUpRight;
	Sprite* mBlockT;

};

#endif