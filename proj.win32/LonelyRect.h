#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class LonelyRect {

	LonelyRect(const char *file) { sprite = Sprite::create(file); }

	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return sprite; }
	void tapIt(){};
	bool containsPoint(Vec2 point){ return sprite->getBoundingBox().containsPoint(point); }
 
private:
	LonelyRect();

	Sprite * sprite;
	bool tapped;
};