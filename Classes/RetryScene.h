#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

using namespace cocos2d;

class RetryScene : public cocos2d::Layer{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// randomly pick background soundtrack
	char* getTrack();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void setUpUI();
	void menuRetryCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuOtherLevelCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuCloseCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuReturnToMainCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuSwitchAudioCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuInfoCallback(Ref* sender, ui::Widget::TouchEventType type);

	LabelTTF *max_score_label;
	// implement the "static node()" method manually
	CREATE_FUNC(RetryScene);
};