#pragma once

#include "cocos2d.h"
#include "TouchableRect.h"
#include "RectPool.h"
#include "SimpleRectFabrik.h"
#include "CocosGUI.h"

using namespace cocos2d;

enum DrawOrder
{
	BackgroundOrder = -1,
	GameElementsOrder,
	UIElementsOrder
};

class GameScene : public Layer
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

private:
	// a selector callbacks
	void menuReturnToMainCallback(Ref* sender, ui::Widget::TouchEventType type);
	bool onTouchBegan(Touch *touch, Event *unused_event);

	//sñhedulers:
	void startSchedule();

	void createRandomRect(float  dt);
	void updateTimer(float dt);
	void checkRectPositions(float  dt);
	void checkScoreProgress();
	void updateLabels();

	//game notofications
	void onGameStart(CCObject* obj);
	void onGameEnd(CCObject* obj);
	void onGamePause(CCObject* obj);
	void onGameResume(CCObject* obj);

	ui::Text* score_label;
	ui::Text* life_label;

	Layer* completed_gui;

	void setUpBackground();
	void setUpUI();

	RectPool rects;
	SimpleRectFarik rectFabrik;

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);
	static int count;

	bool is_playing;
	//time from the onGameStart()
	int time_sec;
	float current_speed;
	
};

