
#include "cocos2d.h"
#include "TouchableRect.h"
#include "RectTrajectory.h"
#include "SimpleRect.h"
#include "LifeRect.h"
#include "DeathRect.h"
#include "ArmoredRect.h"

using namespace cocos2d;

enum FabrikMode {
	RANDOM = 0,
	CROSS,
	CHESS
};

enum RectTyped {
	SIMPLE = 0,
	LIFE,
	DEATH,
	ARMORED
};


class SimpleRectFarik {

public:

	SimpleRectFarik() {

		rect_n = 4;

		auto visibleSize = Director::getInstance()->getVisibleSize();
		TouchableRect* new_rect = new LifeRect(NORMAL_RECT_SPRITE_FILE);
		
		sprite_w = new_rect->getSprite()->boundingBox().size.width;
		scale_w = visibleSize.width / sprite_w / rect_n;
		new_rect->getSprite()->setScale(scale_w);
		sprite_w = new_rect->getSprite()->boundingBox().size.width;

		hide_h = new_rect->getSprite()->boundingBox().size.height;
	 
		mode = RANDOM;
		curr_cross_position = 0;

		trajectory.resize(3);

		trajectory.at(RANDOM) = new RandTrajectory(rect_n);
		trajectory.at(CROSS) = new CrossTrajectory(rect_n);
		trajectory.at(CHESS) = new ChessTrajectory(rect_n);

		rects.resize(4);

		rects.at(SIMPLE) = new SimpleRect();
		rects.at(LIFE) = new LifeRect();
		rects.at(DEATH) = new DeathRect();
		rects.at(ARMORED) = new ArmoredRect();
	}


	TouchableRect *createRect() {

		auto visibleSize = Director::getInstance()->getVisibleSize();
		TouchableRect* new_rect = createRandomRectType();

		new_rect->getSprite()->setScale(scale_w);
		
		int random = calcXPosWithMode();

		int start_pos_x = visibleSize.width - sprite_w * random - sprite_w / 2;

		new_rect->getSprite()->setPosition(Vec2(start_pos_x, visibleSize.height + hide_h/2));

		return new_rect;
	}

	void setMode(FabrikMode _mode) {
		mode = _mode;
	}

	int rect_n; //max  rects per row
	float scale_w; //rect scale
	float sprite_w; //rect width
	float hide_h; //rect height/2

private:

	int calcXPosWithMode() {
		return trajectory.at(mode)->calcPosition();
	}

	TouchableRect* createRandomRectType() {
		int rand_i = rand() % 100;

		//first, simple hardcode it:
	
		if (rand_i < 70) {
			return rects.at(SIMPLE)->clone();
		}
		else if (rand_i < 90) {
			rects.at(3)->clone();
		}
		else if (rand_i < 95) {
			return rects.at(DEATH)->clone();
		}
		else  {
			return rects.at(LIFE)->clone();
		}

	}
	//Usefull prototypes:
	std::vector<RectTrajectory *>  trajectory; 
	std::vector<TouchableRect *>  rects;

	FabrikMode mode;
	int curr_cross_position;

};