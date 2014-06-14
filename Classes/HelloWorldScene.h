#pragma once

#include "cocos2d.h"
#include "LonelyRect.h"
#include "RectManager.h"

#define GAME_START "Game Start"

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
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
    CREATE_FUNC(HelloWorld);
	static int count;

	void updateSpeed(float  dt);
	void checkRectPositions(float  dt);
	void onGameStart(CCObject* obj);

	float getCurrSpeed();
	void setCurrSpeed(float speed);

	LabelTTF* score_label;

private:
	void startSchedule();

	float current_speed;
	float rects_per_h;
	int rect_n;

	RectManager rects;

};

