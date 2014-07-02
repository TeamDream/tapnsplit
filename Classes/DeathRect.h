#include "TouchableRect.h"

#define DEATH_RECT_SPRITE_FILE "RectAnimation/DeathRectAnimation1.png"

class DeathRect : public TouchableRect {
public:
	DeathRect(const char *file1 = DEATH_RECT_SPRITE_FILE) : TouchableRect(file1) {};
private:
	virtual void animate() {
		Animation * anim = Animation::create();
		anim->addSpriteFrameWithFile("RectAnimation/DeathRectAnimation1.png");
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
		SessionController::damage();
	}

	virtual void dieAction() {
		//SessionController::damage();
	}

	virtual TouchableRect* clone() {
		return new DeathRect();
	}

};