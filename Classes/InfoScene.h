#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

using namespace cocos2d;

class InfoScene : public cocos2d::Layer{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuToMainCallback(Ref* sender, ui::Widget::TouchEventType type);
	bool onTouchBegan2(Touch *touch, Event *unused_event);
	void setUpUI();
	EventListenerTouchOneByOne* touchListener;
	// implement the "static node()" method manually
	CREATE_FUNC(InfoScene);

	~InfoScene();
};
 


 