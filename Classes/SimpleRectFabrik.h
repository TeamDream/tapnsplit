
#include "cocos2d.h"
#include "TouchableRect.h"

using namespace cocos2d;

#define RECT_SPRITE_FILE "rect_black.png"

enum FabrikMode {
	RANDOM = 0,
	CROSS,
	DOUBLE_MODE
};


class SimpleRectFarik {

public:

	SimpleRectFarik() {

		rect_n = 4;

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto new_rect = new TouchableRect(RECT_SPRITE_FILE);
		
		sprite_w = new_rect->getSprite()->boundingBox().size.width;
		scale_w = visibleSize.width / sprite_w / rect_n;
		new_rect->getSprite()->setScale(scale_w);
		sprite_w = new_rect->getSprite()->boundingBox().size.width;

		hide_h = new_rect->getSprite()->boundingBox().size.height;
	 
		mode = RANDOM;
		curr_cross_position = 0;
	}


	TouchableRect *createRect() {

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto new_rect = new TouchableRect(RECT_SPRITE_FILE);

		//rect scale:		
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
		switch (mode) {
		case RANDOM:
			return rand() % rect_n;
		case CROSS: //2IMPLEMENT:
			return (curr_cross_position++) % rect_n;
		}
	}

	FabrikMode mode;
	int curr_cross_position;

};