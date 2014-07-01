#pragma once

#include "TouchableRect.h"

class SimpleRect : public TouchableRect {
public:
	SimpleRect(const char *file1) : TouchableRect(file1) {};
private:
	virtual void animate() {
		Animation * anim = Animation::create();
		anim->addSpriteFrameWithFile("RectAnimation/RectAnimation1.png");
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
		SessionController::addScore();
	}

};