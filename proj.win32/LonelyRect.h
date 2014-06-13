#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class LonelyRect {

	LonelyRect(const char *file) { sprite = Sprite::create(file); }
	inline bool isTapped() { return tapped; }
	Sprite *getSprite(){ return sprite; }
private:
	LonelyRect();

	Sprite * sprite;
	bool tapped;
};