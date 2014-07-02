
#include "cocos2d.h"
#include "TouchableRect.h"
#include "RectTrajectory.h"
#include "SimpleRect.h"
#include "LifeRect.h"
#include "DeathRect.h"
using namespace cocos2d;



enum FabrikMode {
	RANDOM = 0,
	CROSS,
	CHESS
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

		rects.resize(3);

		rects.at(0) = new SimpleRect();
		rects.at(1) = new LifeRect();
		rects.at(2) = new DeathRect();
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
		int rand_i = rand() % 10;

		//first, simple hardcode it:

		if (rand_i < 6) {
			return rects.at(0)->clone();
		}
		else if (rand_i < 7) {
			return rects.at(1)->clone();
		}
		else  {
			return rects.at(2)->clone();
		}

	}
	//Usefull prototypes:
	std::vector<RectTrajectory *>  trajectory; 
	std::vector<TouchableRect *>  rects;

	FabrikMode mode;
	int curr_cross_position;

};