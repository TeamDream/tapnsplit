#pragma once

#include "TouchableRect.h"

#define LIFE_RECT_SPRITE_FILE "RectAnimation/LifeRectAnimation1.png"

class LifeRect : public TouchableRect {
public:
	LifeRect(const char *file1 = LIFE_RECT_SPRITE_FILE) : TouchableRect(file1) {};
	
private:
	virtual void animate() {//2DO set right sprites and animation
		Animation * anim = Animation::create();
		anim->addSpriteFrameWithFile("RectAnimation/LifeRectAnimation1.png");
		anim->addSpriteFrameWithFile("RectAnimation/RectAnimation2.png");
		anim->addSpriteFrameWithFile("RectAnimation/RectAnimation3.png");
		anim->addSpriteFrameWithFile("RectAnimation/RectAnimation4.png");
		anim->addSpriteFrameWithFile("RectAnimation/RectAnimation5.png");//little hack

		anim->setDelayPerUnit(0.03);

		Animate *anim_action = Animate::create(anim);

		curr_sprite->runAction(anim_action);
		tapped = true;
	}

	virtual void doAction() {
		SessionController::addLife();
	}
	virtual void dieAction() {
		//SessionController::damage(); //do nothing. Missed life - your probkem
	}
	virtual TouchableRect* clone() {
		return new LifeRect();
	}

};