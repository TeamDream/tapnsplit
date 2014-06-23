#include "LevelScene.h"
#include "GameScene.h"
#include "SessionController.h"
#include "AppMacros.h"

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool LevelScene::init() {

	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto startLevel1 = MenuItemImage::create(
		"2remove/Level1.png",
		"2remove/Level1.png",
		CC_CALLBACK_1(LevelScene::menuStartGameCallback, this, 1));
	auto startLevel2 = MenuItemImage::create(
		"2remove/Level2.png",
		"2remove/Level2.png",
		CC_CALLBACK_1(LevelScene::menuStartGameCallback, this, 2));
	auto startLevel3 = MenuItemImage::create(
		"2remove/Level3.png",
		"2remove/Level3.png",
		CC_CALLBACK_1(LevelScene::menuStartGameCallback, this, 3));

	startLevel1->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, 50));
	startLevel2->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, 0));
	startLevel3->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, -50));
	 

	// create menu, it's an autorelease object
	auto menu_start_game = Menu::create(startLevel1, startLevel2, startLevel3, NULL);
 
	menu_start_game->setPosition(Vec2::ZERO);
 
	this->addChild(menu_start_game, UIElementsOrder);
 
	// create and initialize a label "Score Label"
	LabelTTF *game_name_label = LabelTTF::create("Choose your level", "Arial", TITLE_FONT_SIZE);
	game_name_label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - game_name_label->getContentSize().height));
	game_name_label->setZOrder(UIElementsOrder);
	this->addChild(game_name_label);

	return true;

}

// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* LevelScene::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	LevelScene * layer = LevelScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// a selector callback
void LevelScene::menuStartGameCallback(Ref* sender, int level_i) {

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"press.wav");

	Director::getInstance()->popScene();
	switch (level_i) {
		case 3:
			SessionController::setSpeed(1.0f);
			break;
		case 2:
			SessionController::setSpeed(2.0f);
			break;
		default:
			SessionController::setSpeed(3.0f);
			break;
	}
	CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
}

void LevelScene::menuCloseCallback(Ref* sender)
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