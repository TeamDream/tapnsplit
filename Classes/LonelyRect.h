#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class LonelyRect {

	LonelyRect(const char *file1, const char *file2) {
		curr_sprite = Sprite::create(file1);
		prev_sprite = Sprite::create(file2);
	}

	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return curr_sprite; }
	//void tapIt(){
	//	Sprite *temp
	//};//just switch sprites
	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

private:
	LonelyRect();

	Sprite * curr_sprite;
	Sprite * prev_sprite;
	bool tapped;
};