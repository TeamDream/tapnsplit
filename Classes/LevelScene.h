#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CocosGUI.h"

using namespace cocos2d;
using namespace ui;

#define LEVEL_COUNT 4

struct LevelInfo {
	Sprite * background = NULL;
	//2D0: replace it by sprite label later
	LabelTTF *label = NULL;

	~LevelInfo() {
		//if (background) background->release();
		//if (label) label->release();
	};
};


class LevelScene : public cocos2d::LayerColor{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuChangeLevelLeft(Ref* sender, Widget::TouchEventType type);
	void menuChangeLevelRight(Ref* sender, Widget::TouchEventType type);
	void menuStartGameCallback(Ref* sender, Widget::TouchEventType type);
	void menuCloseCallback(Ref* sender);


	void loadLevelInfo();

	std::map<int, LevelInfo> level_info;

	// implement the "static node()" method manually
	CREATE_FUNC(LevelScene);
	 
};