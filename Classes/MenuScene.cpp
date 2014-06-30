#include "MenuScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "AppMacros.h"
#include "cocostudio/WidgetReader/WidgetReader.h"


using namespace ui;

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MenuScene::init() {

	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"background_m.mp3", true);

	setUpUI();

	return true;
}

void MenuScene::setUpUI() {
	
	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("StartScene/StartScene.json"));
	this->addChild(m_pLayout);

	auto start_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Start"));
	start_game->addTouchEventListener(CC_CALLBACK_2(MenuScene::menuStartGameCallback, this));

	auto exit_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Exit"));
	exit_game->addTouchEventListener(CC_CALLBACK_2(MenuScene::menuCloseCallback, this));
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
void MenuScene::menuStartGameCallback(Ref* sender, Widget::TouchEventType type) {
	
	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"press.wav");
	Scene *s = LevelScene::scene();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,s));
	
}

void MenuScene::menuCloseCallback(Ref* sender, Widget::TouchEventType type)
{

	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}