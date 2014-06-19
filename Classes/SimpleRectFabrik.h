
#include "cocos2d.h"
#include "TouchableRect.h"

using namespace cocos2d;

#define RECT_SPRITE_FILE "rect_black.png"

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
	 
	}


	TouchableRect *createRect() {

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto new_rect = new TouchableRect(RECT_SPRITE_FILE);

		//rect scale:		
		new_rect->getSprite()->setScale(scale_w);
		
		int random = rand() % rect_n;
		int start_pos_x = visibleSize.width - sprite_w * random - sprite_w / 2;

		new_rect->getSprite()->setPosition(Vec2(start_pos_x, visibleSize.height + hide_h/2));

		return new_rect;
	}

	int rect_n; //max  rects per row
	float scale_w; //rect scale
	float sprite_w; //rect width
	float hide_h; //rect height/2

};