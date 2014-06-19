#pragma once

#include "cocos2d.h"
#include "TouchableRect.h"
#include "RectPool.h"
#include "SimpleRectFabrik.h"

#define GAME_START "Game Start"

using namespace cocos2d;

enum DrawOrder
{
	GameElementsOrder = 0,
	UIElementsOrder
};

class GameScene : public cocos2d::LayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
	bool onTouchBegan(Touch* touch, Event* event);

	void createRandomRect(float  dt);
	void spriteMoveFinished(CCNode* sender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
	static int count;

	void updateSpeed(float  dt);
	void checkRectPositions(float  dt);
	void onGameStart(CCObject* obj);

	LabelTTF* score_label;

private:
	void startSchedule();
	void setUpUI();


	float current_speed;
	float prev_speed;

	bool speed_changed;

	RectPool rects;
	SimpleRectFarik rectFabrik;

};

