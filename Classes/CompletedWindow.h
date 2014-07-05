#pragma once

#include "cocos2d.h"

#include "CocosGUI.h"

using namespace cocos2d;

class CompletedWindow : public cocos2d::Layer{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuContinueGameCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuToLevelMenu(Ref* sender, ui::Widget::TouchEventType type);

	void setUpUI();
 
	// implement the "static node()" method manually
	CREATE_FUNC(CompletedWindow);
};