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

	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return curr_sprite; }
	
	void tapIt() { //just switch 2 sprites

		if (!tapped) {
			animate();
			doAction();
		}
	}; 

	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

	virtual void animate() = 0; //call animation, set it as tapped
	virtual void doAction() = 0; //concrete rect action
	virtual void dieAction() = 0; //action for missed rect -  rect gets to the border screen alive
	virtual TouchableRect* clone() = 0;

protected:
	TouchableRect();

	Sprite * curr_sprite;
 
	bool tapped;
};