#pragma once
#include "cocos2d.h"

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

			Animation * anim = Animation::create();
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation1.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation2.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation3.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation4.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation5.png");//little hack

			anim->setDelayPerUnit(0.03);

			Animate *anim_action = Animate::create(anim);

			curr_sprite->runAction(anim_action);
			//curr_sprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(NON_ACTIVE_RECT));
			tapped = true;
		}
	}; 

	bool containsPoint(Vec2 point){ return curr_sprite->getBoundingBox().containsPoint(point); }

private:
	TouchableRect();

	Sprite * curr_sprite;
 
	bool tapped;
};