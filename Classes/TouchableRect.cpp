#include "TouchableRect.h"

void TouchableRect::onEnter(){
    // before 2.0:
    // CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);

    // since 2.0: 
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TouchableRect::onTouchBegan, this);
	Director::sharedDirector()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);
    Sprite::onEnter();
}
void TouchableRect::onExit(){
    // before 2.0:
    // CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);

    // since 2.0:
	//Director::sharedDirector()->getEventDispatcher()->removeEventListener();
    Sprite::onExit();
}
bool TouchableRect::onTouchBegan(Touch* touch, Event* event){
//do whatever you want here
	CCLog("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
    return true;
}
void TouchableRect::onTouchMoved(Touch* touch, Event* event){
    //do what you want
}
void TouchableRect::onTouchEnded(Touch* touch, Event* event){
//do your job here
}