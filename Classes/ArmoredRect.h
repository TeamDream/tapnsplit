#pragma once

#include "TouchableRect.h"
class ArmoredRect : public TouchableRect {
public :
	ArmoredRect() {
		tapped_count = 0;
		setUpSprite();
	}

private:

	virtual void setUpSprite() {
		level_i = SessionController::curr_level;

		if (level_i == 4) {
			level_i = rand() % 3 + 1;
		}

		char level_s[50];
		sprintf(level_s, "GAMEPLAY/level%d/gameplay%d_armorBlock_sprite%d.png", level_i, level_i, 1);
		curr_sprite = Sprite::create(level_s);
	}

	virtual void animate() {//2DO set right sprites and animation

		++tapped_count;

		Animation * anim = Animation::create();

		char level_s[50];
		sprintf(level_s, "GAMEPLAY/level%d/gameplay%d_armorBlock_sprite%d.png", level_i, level_i, 2);
		if (tapped_count == 1) { //2 touches
			anim->addSpriteFrameWithFile(level_s);
		}
		else {
			for (int i = 2; i < 6; i++) {
				sprintf(level_s, "GAMEPLAY/level%d/gameplay%d_armorBlock_sprite%d.png", level_i, level_i, i);
				anim->addSpriteFrameWithFile(level_s);
			}
			anim->addSpriteFrameWithFile("GAMEPLAY/empty_sprite.png");
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
		SessionController::damageLife(); //do nothing. Missed life - your probkem
	}
	virtual TouchableRect* clone() {
		return new ArmoredRect();
	}

	int tapped_count;

};