#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class LevelScene : public cocos2d::LayerColor{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuStartGameCallback(Ref* sender, int level_i);
	void menuCloseCallback(Ref* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(LevelScene);
};