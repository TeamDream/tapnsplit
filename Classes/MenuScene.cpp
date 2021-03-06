#include "MenuScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "AppMacros.h"
#include "cocostudio/WidgetReader/WidgetReader.h"
#include "AudioEngineWrapper.h"
#include "InfoScene.h"

using namespace ui;

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MenuScene::init() {

	if (!Layer::init())
	{
		return false;
	}

	AudioEngineWrapper::getInstance()->playStartSong();
	//AudioEngineWrapper::getInstance()->turnVolumeOff(true);
	setUpUI();

	return true;
}

void MenuScene::setUpUI() {

	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("StartScene/StartScene.json"));
	m_pLayout->setTag(0);
	this->addChild(m_pLayout);


	//manual correction of UI positions. COCOS2dX bug????
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto layout_childs = m_pLayout->getChildren();
	for (auto curr_child = layout_childs.begin(); curr_child != layout_childs.end(); curr_child++) {
		auto wrapped_child = dynamic_cast<Widget*> (*curr_child);
		wrapped_child->setPositionType(Widget::PositionType::ABSOLUTE);
		wrapped_child->setPositionY(origin.y + visibleSize.height*wrapped_child->getPositionPercent().y);
		wrapped_child->setPositionX(origin.x + visibleSize.width*wrapped_child->getPositionPercent().x);
	}

	auto start_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Start"));
	start_game->addTouchEventListener(CC_CALLBACK_2(MenuScene::menuStartGameCallback, this));

	auto info = dynamic_cast<Button*>(m_pLayout->getChildByName("info"));
	info->addTouchEventListener(CC_CALLBACK_2(MenuScene::menuInfoCallback, this));

	auto exit_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Exit"));
	exit_game->addTouchEventListener(CC_CALLBACK_2(MenuScene::menuCloseCallback, this));

	auto audio_switcher = dynamic_cast<Button*>(m_pLayout->getChildByName("Audio"));
	audio_switcher->addTouchEventListener(CC_CALLBACK_2(MenuScene::menuSwitchAudioCallback, this));
	if (!AudioEngineWrapper::getInstance()->isSoundEnabled()) {
		audio_switcher->setBright(false);
		AudioEngineWrapper::getInstance()->turnVolumeOff(true);
	}
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

	AudioEngineWrapper::getInstance()->playPressEffect();


	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	bool f_launch = def->getBoolForKey("NOT_FIRST_LAUNCH");

	if (!f_launch) {
		Scene *s = InfoScene::scene();
		Director::getInstance()->replaceScene(CCTransitionCrossFade::create(0.5, s));
		def->setBoolForKey("NOT_FIRST_LAUNCH", true);
		def->flush();
	} else {
		Scene *s = LevelScene::scene();
		Director::getInstance()->replaceScene(CCTransitionCrossFade::create(0.5, s));
	}
 
}

void MenuScene::menuInfoCallback(Ref* sender, ui::Widget::TouchEventType type) {

	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

	AudioEngineWrapper::getInstance()->playPressEffect();

	Scene *s = InfoScene::scene();
	Director::getInstance()->replaceScene(CCTransitionCrossFade::create(0.5, s));
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

void MenuScene::menuSwitchAudioCallback(Ref* sender, ui::Widget::TouchEventType type) {

	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

	Layout *m_pLayout = dynamic_cast<Layout *> (this->getChildByTag(0));

	auto audio_switcher = dynamic_cast<Button*>(m_pLayout->getChildByName("Audio"));

	if (audio_switcher->isBright()) {
		audio_switcher->setBright(false);
		AudioEngineWrapper::getInstance()->turnVolumeOff(true);
	}
	else {
		audio_switcher->setBright(true);
		AudioEngineWrapper::getInstance()->turnVolumeOff(false);
	}

}