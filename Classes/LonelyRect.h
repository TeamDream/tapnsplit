#pragma once
#include "cocos2d.h"

using namespace cocos2d;

#define NON_ACTIVE_RECT "rect_blue.png"

class LonelyRect {
public:
	LonelyRect(const char *file1) {
		curr_sprite = Sprite::create(file1);
	}

	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return curr_sprite; }
	
	void tapIt() { //just switch 2 sprites
		curr_sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(NON_ACTIVE_RECT));
	}; 

	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

private:
	LonelyRect();

	Sprite * curr_sprite;
 
	bool tapped;
};