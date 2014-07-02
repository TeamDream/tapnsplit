#pragma once

#include "TouchableRect.h"

#define ARMORED_RECT_SPRITE_FILE "RectAnimation/ArmoredRectAnimation1.png"

class ArmoredRect : public TouchableRect {
public:
	ArmoredRect(const char *file1 = ARMORED_RECT_SPRITE_FILE) : TouchableRect(file1), tapped_count(0) {};

private:
	virtual void animate() {//2DO set right sprites and animation

		++tapped_count;

		Animation * anim = Animation::create();

		if (tapped_count == 1) { //2 touches
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation1.png");
		}
		else {
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation1.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation2.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation3.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation4.png");
			anim->addSpriteFrameWithFile("RectAnimation/RectAnimation5.png");//little hack

			tapped = true;
		}

		anim->setDelayPerUnit(0.03);

		Animate *anim_action = Animate::create(anim);

		curr_sprite->runAction(anim_action);
	}

	virtual void doAction() {
		if (tapped_count < 2) {
			SessionController::addScore();
		}
	}
	virtual void dieAction() {
		SessionController::damage(); //do nothing. Missed life - your probkem
	}
	virtual TouchableRect* clone() {
		return new ArmoredRect();
	}

	int tapped_count;

};