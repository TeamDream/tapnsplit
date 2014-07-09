#include "RetryScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "MenuScene.h"
#include "InfoScene.h"
#include "SessionController.h"
#include "AppMacros.h"
#include "AudioEngineWrapper.h"
#include "cocostudio/WidgetReader/WidgetReader.h"

using namespace ui;

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool RetryScene::init() {

	AudioEngineWrapper::getInstance()->playGameOver();
	AudioEngineWrapper::getInstance()->playRandomTrack();

	if (!Layer::init()) //RGBA
	{
		return false;
	}

	setUpUI();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
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

void RetryScene::setUpUI() {

	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("RetryScene/RetryScene.json"));
	m_pLayout->setTag(0);
	this->addChild(m_pLayout);

	auto start_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Retry"));
	start_game->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuRetryCallback, this));

	auto change_level = dynamic_cast<Button*>(m_pLayout->getChildByName("ChangeLevel"));
	change_level->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuOtherLevelCallback, this));

	auto to_main_menu = dynamic_cast<Button*>(m_pLayout->getChildByName("Menu"));
	to_main_menu->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuReturnToMainCallback, this));

	auto exit_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Exit"));
	exit_game->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuCloseCallback, this));

	auto info = dynamic_cast<Button*>(m_pLayout->getChildByName("info"));
	info->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuInfoCallback, this));

	auto highest_score = dynamic_cast<Text*>(m_pLayout->getChildByName("HighestScoreLabel"));
	std::stringstream ss;
	ss << "Highest Score: " << SessionController::getHighScore();
	highest_score->setText(ss.str());
	highest_score->setFontName("fonts/Myriad Pro.ttf");

	auto current_score = dynamic_cast<Text*>(m_pLayout->getChildByName("ScoreLabel"));
	std::stringstream ss2;
	ss2 << "Current Score: " << SessionController::getScore();
	current_score->setText(ss2.str());
	current_score->setFontName("fonts/Myriad Pro.ttf");

	auto audio_switcher = dynamic_cast<Button*>(m_pLayout->getChildByName("Audio"));
	audio_switcher->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuSwitchAudioCallback, this));
	
	if (!AudioEngineWrapper::getInstance()->isSoundEnabled()) {
		audio_switcher->setBright(false);
		AudioEngineWrapper::getInstance()->turnVolumeOff(true);
	}
}

// a selector callback
void RetryScene::menuRetryCallback(Ref* sender, Widget::TouchEventType type) {
	
	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

	Director::getInstance()->popScene();
	
	CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
	AudioEngineWrapper::getInstance()->playPressEffect();

	SessionController::init();
}
 
// a selector callback
void RetryScene::menuOtherLevelCallback(Ref* sender, Widget::TouchEventType type) {
	
	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

	Director::getInstance()->popScene();

	auto level_choose = LevelScene::scene();
	Director::getInstance()->pushScene(level_choose);
 
}

void RetryScene::menuReturnToMainCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}
		Director::getInstance()->popScene();

		auto main_menu = MenuScene::scene();
		Director::getInstance()->pushScene(main_menu);

}

void RetryScene::menuCloseCallback(Ref* sender, Widget::TouchEventType type)
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

void RetryScene::menuSwitchAudioCallback(Ref* sender, ui::Widget::TouchEventType type) {


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


void RetryScene::menuInfoCallback(Ref* sender, ui::Widget::TouchEventType type) {

	if (type != Widget::TouchEventType::ENDED) { //process only finished touches
		return;
	}

	AudioEngineWrapper::getInstance()->playPressEffect();

	Scene *s = InfoScene::scene();
	Director::getInstance()->replaceScene(CCTransitionCrossFade::create(0.5, s));
}