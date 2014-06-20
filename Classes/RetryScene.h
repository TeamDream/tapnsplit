#pragma once

#include "cocos2d.h"
 
using namespace cocos2d;

class RetryScene : public cocos2d::LayerColor{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// randomly pick background soundtrack
	char* getTrack();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuRetryCallback(Ref* sender);
	void menuCloseCallback(Ref* sender);

	LabelTTF *max_score_label;
	// implement the "static node()" method manually
	CREATE_FUNC(RetryScene);
};