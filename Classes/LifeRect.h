#pragma once

#include "TouchableRect.h"

#define LIFE_RECT_SPRITE_FILE "RectAnimation/LifeRectAnimation1.png"

class LifeRect : public TouchableRect {
public:
	LifeRect() {
		setUpSprite();
	}

private:
	virtual void setUpSprite() {
		curr_sprite = Sprite::create("GAMEPLAY/gameplay_lifeBlock_sprite1.png");
	}

	virtual void animate() {//2DO set right sprites and animation
		Animation * anim = Animation::create();

		char level_s[50];

		for (int i = 1; i < 5; i++) {
			sprintf(level_s, "GAMEPLAY/gameplay_lifeBlock_sprite%d.png", i);
			anim->addSpriteFrameWithFile(level_s);
		}
		anim->addSpriteFrameWithFile("GAMEPLAY/empty_sprite.png");
		anim->setDelayPerUnit(0.03);

		Animate *anim_action = Animate::create(anim);

		curr_sprite->runAction(anim_action);
		tapped = true;
	}

	virtual void doAction() {
		SessionController::addScore();
		SessionController::addLife();
	}
	virtual void dieAction() {
		//SessionController::damage(); //do nothing. Missed life - your probkem
	}
	virtual TouchableRect* clone() {
		return new LifeRect();
	}

};