#include "RetryScene.h"
#include "GameScene.h"
#include "SessionController.h"

char* RetryScene::getTrack() {
	int sounds_n = 6;
	int random = rand() % sounds_n;
	char* music;

	switch (random) {
	case 0:
		music = "tiger.mp3";
		break;
	case 1:
		music = "1.mp3";
		break;
	case 2:
		music = "background-musiñ.mp3";
		break;
	case 3:
		music = "stronger.mp3";
		break;
	case 4:
		music = "lucky.mp3";
		break;
	case 5:
		music = "throne.mp3";
		break;
	}
	return music;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool RetryScene::init() {

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"gameover.mp3");
	char * music = getTrack();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		music, true);

	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto retryItem = MenuItemImage::create(
		"Retry.png",
		"RetrySelected.png",
		CC_CALLBACK_1(RetryScene::menuRetryCallback, this));
	auto closeItem = MenuItemImage::create(
		"Exit.png",
		"ExitSelected.png",
		CC_CALLBACK_1(RetryScene::menuCloseCallback, this));

	retryItem->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, 50));
	closeItem->setPosition(origin + Vec2(visibleSize) / 2 - Vec2(0, retryItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu_retry = Menu::create(retryItem, NULL);
	auto menu_close = Menu::create(closeItem, NULL);

	menu_retry->setPosition(Vec2::ZERO);
	menu_close->setPosition(Vec2::ZERO);

	this->addChild(menu_retry, UIElementsOrder);
	this->addChild(menu_close, UIElementsOrder);

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
	//somehow switch to GameScene scene
//	Scene *s = GameScene::scene();
	//Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,s));
	Director::getInstance()->popScene();

	CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"press.wav");
	SessionController::init();
}

void RetryScene::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}