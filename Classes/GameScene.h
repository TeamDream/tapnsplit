#pragma once

#include "cocos2d.h"
#include "TouchableRect.h"
#include "RectPool.h"
#include "SimpleRectFabrik.h"

using namespace cocos2d;

enum DrawOrder
{
	BackgroundOrder = -1,
	GameElementsOrder,
	UIElementsOrder
};

class GameScene : public cocos2d::LayerColor
{
public:
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

private:
	// a selector callbacks
	void menuCloseCallback(Ref* sender);
	bool onTouchBegan(Touch* touch, Event* event);

	//sñhedulers:
	void startSchedule();

	void createRandomRect(float  dt);
	void updateTimer(float dt);
	void checkRectPositions(float  dt);
	void updateLabels();
	//game notofications
	void onGameStart(CCObject* obj);
	void onGameEnd(CCObject* obj);

	LabelTTF* score_label;
	LabelTTF* time_label;

	void setUpUI();

	//time from the onGameStart()
	int time_sec;

	float current_speed;

	RectPool rects;
	SimpleRectFarik rectFabrik;

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);
	static int count;

	bool is_playing;
	
};

