#pragma once
#include "cocos2d.h"
#include "SessionController.h"

using namespace cocos2d;

#define NON_ACTIVE_RECT "RectAnimation/RectAnimation4.png"

class TouchableRect {
public:
	TouchableRect(const char *file1) {
		curr_sprite = Sprite::create(file1);
		tapped = false;
	}

	~TouchableRect() {
		curr_sprite->release();
	}

	virtual void animate() = 0;
	virtual void doAction() = 0;
	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return curr_sprite; }
	
	void tapIt() { //just switch 2 sprites

		if (!tapped) {
			animate();
			doAction();
		}
	}; 

	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

protected:
	TouchableRect();

	Sprite * curr_sprite;
 
	bool tapped;
};