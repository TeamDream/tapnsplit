#pragma once

#include "TouchableRect.h"

class SimpleRect : public TouchableRect {
public:
	SimpleRect() {
		setUpSprite();
	}

private:
	virtual void setUpSprite() {
	
		level_i = SessionController::curr_level;

		if (level_i == 4) {
			level_i = rand() % 3 + 1;
		}

		char level_s[50];
		sprintf(level_s, "GAMEPLAY/level%d/gameplay%d_normalBlock_sprite%d.png", level_i, level_i, 1);
		curr_sprite = Sprite::create(level_s);
	}

	virtual void animate() {
		Animation * anim = Animation::create();

		char level_s[50];

		for (int i = 1; i < 5; i++) {
			sprintf(level_s, "GAMEPLAY/level%d/gameplay%d_normalBlock_sprite%d.png", level_i, level_i, i);
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
	}

	virtual void dieAction() {
		SessionController::damageLife();
	}

	virtual TouchableRect* clone() {
		return new SimpleRect();
	}


};