#pragma once
#include "cocos2d.h"

using namespace cocos2d;

#define NON_ACTIVE_RECT "rect_blue.png"

class TouchableRect {
public:
	TouchableRect(const char *file1) {
		curr_sprite = Sprite::create(file1);
		tapped = false;
	}

	~TouchableRect() {
		curr_sprite->release();
	}

	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return curr_sprite; }
	
	void tapIt() { //just switch 2 sprites
		curr_sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(NON_ACTIVE_RECT));
		tapped = true;
	}; 

	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

private:
	TouchableRect();

	Sprite * curr_sprite;
 
	bool tapped;
};