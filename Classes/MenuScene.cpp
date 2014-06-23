#include "MenuScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "AppMacros.h"

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MenuScene::init() {

	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
	//	"background_m.mp3", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto startItem = MenuItemImage::create(
		"NewGame.png",
		"NewGameSelected.png",
		CC_CALLBACK_1(MenuScene::menuStartGameCallback, this));
	auto closeItem = MenuItemImage::create(
		"Exit.png",
		"ExitSelected.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	startItem->setPosition(origin + Vec2(visibleSize) / 2 + Vec2(0, 50));
	closeItem->setPosition(origin + Vec2(visibleSize) / 2 - Vec2(0, startItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu_start_game = Menu::create(startItem, NULL);
	auto menu_close = Menu::create(closeItem, NULL);

	menu_start_game->setPosition(Vec2::ZERO);
	menu_close->setPosition(Vec2::ZERO);

	this->addChild(menu_start_game, UIElementsOrder);
	this->addChild(menu_close, UIElementsOrder);


	// create and initialize a label "Score Label"
	LabelTTF *game_name_label = LabelTTF::create("THE GAME", "Arial", TITLE_FONT_SIZE);
	game_name_label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - game_name_label->getContentSize().height));
	game_name_label->setZOrder(UIElementsOrder);
	this->addChild(game_name_label);

	// create and initialize a label "Score Label"
	auto credits = LabelTTF::create("Made by CoCoCoTEAM", "Arial", TITLE_FONT_SIZE);
	credits->setPosition(Vec2(origin.x + visibleSize.width / (1.5),
		origin.y + credits->getContentSize().height)); 
	credits->setZOrder(UIElementsOrder);
	this->addChild(credits);

	return true;

}

// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* MenuScene::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	MenuScene * layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// a selector callback
void MenuScene::menuStartGameCallback(Ref* sender) {
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"press.wav");
	Scene *s = LevelScene::scene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,s));
	
}

void MenuScene::menuCloseCallback(Ref* sender)
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