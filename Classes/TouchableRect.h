#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class TouchableRect : public Sprite, public TargetedAction
{
    public:
    virtual void onEnter();
    virtual void onExit();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
};

