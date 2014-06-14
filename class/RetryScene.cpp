#include "RetryScene.h"
#include "HelloWorldScene.h"

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool RetryScene::init() {

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto retryItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(RetryScene::menuRetryCallback, this));

	retryItem->setPosition(origin + Vec2(visibleSize) / 2 - Vec2(retryItem->getContentSize() / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(retryItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;

}

// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* RetryScene::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	RetryScene * layer = RetryScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// a selector callback
void RetryScene::menuRetryCallback(Ref* sender) {
	//somehow switch to HelloWorld scene
	Scene *s = HelloWorld::scene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,s));

	CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
}