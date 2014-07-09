#pragma once
#include "cocos2d.h"
#include "SessionController.h"

using namespace cocos2d;

class TouchableRect {
public:
	TouchableRect() {
		tapped = false;
	}

	~TouchableRect() {
		curr_sprite->release();
	}

	inline bool isTapped() { return tapped; }
	Sprite *getSprite() { return curr_sprite; }
	
	void tapIt() { //animate and do something

		if (!tapped) {
			animate();
			doAction();
		}
	}; 

	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

	virtual void animate() = 0; //call animation, set it as tapped
	virtual void doAction() = 0; //concrete rect action
	virtual void dieAction() = 0; //action for missed rect -  rect gets to the border screen alive
	virtual void setUpSprite() = 0; //load special sprite for each subclass
	virtual TouchableRect* clone() = 0;

protected:

	Sprite * curr_sprite;
	int level_i;
	bool tapped;
};