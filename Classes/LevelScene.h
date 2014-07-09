#pragma once

#include "cocos2d.h"
#include "CocosGUI.h"

using namespace cocos2d;
using namespace ui;

#define LEVEL_COUNT 4

class LevelScene : public cocos2d::Layer{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuChangeLevelLeft(Ref* sender, Widget::TouchEventType type);
	void menuChangeLevelRight(Ref* sender, Widget::TouchEventType type);
	void menuStartGameCallback(Ref* sender, Widget::TouchEventType type);
	void menuReturnToMainCallback(Ref* sender, Widget::TouchEventType type);
	void menuSwitchAudioCallback(Ref* sender, ui::Widget::TouchEventType type);
	void menuInfoCallback(Ref* sender, ui::Widget::TouchEventType type);

	void loadLevelInfo();
	void initUI(int level_i = 1);
	void changeLevelUI(int level_i = 1);

	LabelTTF *level_name;
	Text* best_level_score;

	inline void updateScoreLabel();
	// implement the "static node()" method manually
	CREATE_FUNC(LevelScene);

};