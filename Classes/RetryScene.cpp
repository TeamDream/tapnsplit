#include "RetryScene.h"
#include "GameScene.h"
#include "SessionController.h"
#include "AppMacros.h"
#include "LevelScene.h"

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
		music = "background_m.mp3";
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

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
	//	"gameover.mp3");
	//char * music = getTrack();
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
	//	music, true);

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
	auto levelsItem = MenuItemImage::create(
		"OtherLevel.png",
		"OtherLevelSelected.png",
		CC_CALLBACK_1(RetryScene::menuOtherLevelCallback, this));
	auto closeItem = MenuItemImage::create(
		"Exit.png",
		"ExitSelected.png",
		CC_CALLBACK_1(RetryScene::menuCloseCallback, this));

	retryItem->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, 50));
	levelsItem->setPosition(origin + Vec2(visibleSize) / 2);
	closeItem->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, -50));

	// create menu, it's an autorelease object
	auto menu_retry = Menu::create(retryItem, levelsItem, closeItem, NULL);

	menu_retry->setPosition(Vec2::ZERO);

	this->addChild(menu_retry, UIElementsOrder);

	// create and initialize a label "Score Label"
	LabelTTF *max_score_label = LabelTTF::create("Max Score Label", "Arial", TITLE_FONT_SIZE);
	max_score_label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - max_score_label->getContentSize().height));
	max_score_label->setZOrder(UIElementsOrder);
	
	//2DO: not a good place for score logic, replace it later
	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	int highest_scrore =  def->getIntegerForKey(HIGHEST_SCORE);
	int curr_score = SessionController::getScore();

	if (highest_scrore < curr_score) {
		highest_scrore = curr_score;
		def->setIntegerForKey(HIGHEST_SCORE, highest_scrore);
		def->flush();
	}
	std::stringstream ss;
	ss << "Highest score: " << highest_scrore << std::endl << "Current score: " << curr_score;
	max_score_label->setString(ss.str());
	this->addChild(max_score_label);

	auto credits = LabelTTF::create("Maded by CoCoCoTEAM", "Arial", TITLE_FONT_SIZE);
	credits->setPosition(Vec2(origin.x + visibleSize.width / (1.5),
		origin.y + credits->getContentSize().height));
	credits->setZOrder(UIElementsOrder);
	this->addChild(credits);

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
	
	Director::getInstance()->popScene();

	CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"press.wav");
	SessionController::init();
}
 
// a selector callback
void RetryScene::menuOtherLevelCallback(Ref* sender) {

	Director::getInstance()->popScene();

	auto level_choose = LevelScene::scene();
	Director::getInstance()->pushScene(level_choose);
 
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