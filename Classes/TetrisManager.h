#ifndef __TETRISMANAGER_H__
#define __TETRISMANAGER_H__

#include "cocos2d.h"

class TetrisManager : public cocos2d::Ref
{
private:
	void makeNewBlock();
	std::vector<unsigned int> mTopOffsets;

private:
	static const int KColumn = 10;
	static const int KRow = 20;
	

};

#endif