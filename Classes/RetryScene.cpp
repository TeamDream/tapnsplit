#include "RetryScene.h"
#include "GameScene.h"
#include "SessionController.h"
#include "AppMacros.h"
#include "LevelScene.h"
#include "MenuScene.h"

#include "cocostudio/WidgetReader/WidgetReader.h"

using namespace ui;

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

	if (!Layer::init()) //RGBA
	{
		return false;
	}

	setUpUI();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	//2DO: not a good place for score logic, replace it later
	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	int highest_scrore = SessionController::getHighScore();// def->getIntegerForKey(HIGHEST_SCORE);
	int curr_score = SessionController::getScore();

	if (highest_scrore < curr_score) {
		SessionController::setHighScore(curr_score);
	}

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
	this->addChild(m_pLayout);

	auto start_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Retry"));
	start_game->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuRetryCallback, this));

	auto change_level = dynamic_cast<Button*>(m_pLayout->getChildByName("ChangeLevel"));
	change_level->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuOtherLevelCallback, this));

	auto to_main_menu = dynamic_cast<Button*>(m_pLayout->getChildByName("Menu"));
	to_main_menu->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuReturnToMainCallback, this));

	auto exit_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Exit"));
	exit_game->addTouchEventListener(CC_CALLBACK_2(RetryScene::menuCloseCallback, this));

	auto highest_score = dynamic_cast<Text*>(m_pLayout->getChildByName("HighestScoreLabel"));
	std::stringstream ss;
	ss << "      Highest Score: " << SessionController::getHighScore();
	highest_score->setText(ss.str());

	auto current_score = dynamic_cast<Text*>(m_pLayout->getChildByName("ScoreLabel"));
	std::stringstream ss2;
	ss2 << "      Current Score: " << SessionController::getScore();
	current_score->setText(ss2.str());
}

// a selector callback
void RetryScene::menuRetryCallback(Ref* sender, Widget::TouchEventType type) {
	
	Director::getInstance()->popScene();

	CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		"press.wav");
	SessionController::init();
}
 
// a selector callback
void RetryScene::menuOtherLevelCallback(Ref* sender, Widget::TouchEventType type) {

	Director::getInstance()->popScene();

	auto level_choose = LevelScene::scene();
	Director::getInstance()->pushScene(level_choose);
 
}

void RetryScene::menuReturnToMainCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		Director::getInstance()->popScene();

		auto main_menu = MenuScene::scene();
		Director::getInstance()->pushScene(main_menu);
	}
}

void RetryScene::menuCloseCallback(Ref* sender, Widget::TouchEventType type)
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