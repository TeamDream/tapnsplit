#include "LevelScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SessionController.h"
#include "AppMacros.h"
#include "cocostudio/WidgetReader/WidgetReader.h"
#include "AudioEngineWrapper.h"

using namespace ui;

void LevelScene::loadLevelInfo() {

	LevelInfo curr;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Impact", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setString("Level 1");
	curr.label->setZOrder(UIElementsOrder);
	curr.label->retain();

	level_info[1] = curr;

	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Impact", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setString("Level 2");
	curr.label->setZOrder(UIElementsOrder);
	curr.label->retain();

	level_info[2] = curr;


	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Impact", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setZOrder(UIElementsOrder);
	curr.label->setString("Level 3");
	curr.label->retain();

	level_info[3] = curr;

	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Impact", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setZOrder(UIElementsOrder);
	curr.label->setString("SURVIVAL MODE");
	curr.label->retain();

	level_info[4] = curr;
}

void LevelScene::changeLevelUI(int level_i ) {
	char level_name[50];
	sprintf(level_name, "LevelScene/LevelScene_%d.json", level_i);

	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile(level_name));
	ImageView* new_background = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Background"));

	auto curr_background = dynamic_cast<Layout *> (this->getChildByTag(0))->getChildByName("Background");
	dynamic_cast<Layout *> (this->getChildByTag(0))->removeChild(curr_background);
	dynamic_cast<Layout *> (this->getChildByTag(0))->addChild(new_background->clone());

	auto new_foreground = dynamic_cast<ImageView*>(m_pLayout->getChildByName("CentralImage"));

	Layout *curr_Layout = dynamic_cast<Layout *> (this->getChildByTag(0));
	auto curr_foreground = curr_Layout->getChildByName("CentralImage");
	
	curr_Layout->removeChild(curr_foreground);
	curr_Layout->addChild(new_foreground->clone());
	
	auto play_btn = dynamic_cast<Button*>(curr_Layout->getChildByName("Play"));

	if (!SessionController::isLevelUnlocked(level_i)) {
		play_btn->setBright(false);
	}
	else {
		play_btn->setBright(true);
	}
	 
}
void LevelScene::initUI(int level_i) {
	char level_name[50];
	sprintf(level_name, "LevelScene/LevelScene_%d.json", level_i);

	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile(level_name));
	m_pLayout->setTag(0);
	this->addChild(m_pLayout);

	Button* start_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Play"));
	start_game->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuStartGameCallback, this));
	Button* move_left = dynamic_cast<Button*>(m_pLayout->getChildByName("MoveLeft"));
	move_left->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuChangeLevelLeft, this));
	Button* move_right = dynamic_cast<Button*>(m_pLayout->getChildByName("MoveRight"));
	move_right->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuChangeLevelRight, this));
	Button* to_main_menu = dynamic_cast<Button*>(m_pLayout->getChildByName("Menu"));
	to_main_menu->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuReturnToMainCallback, this));

	//set up audio stuff
	auto audio_switcher = dynamic_cast<Button*>(m_pLayout->getChildByName("Audio"));
	audio_switcher->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuSwitchAudioCallback, this));

	if (!AudioEngineWrapper::getInstance()->isSoundEnabled()) {
		audio_switcher->setBright(false);
		AudioEngineWrapper::getInstance()->turnVolumeOff(true);
	}

	best_level_score = dynamic_cast<Text*>(m_pLayout->getChildByName("Score"));
	best_level_score->setFontName("Myriad Pro");
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool LevelScene::init() {

	if (!Layer::init()) //RGBA
	{
		return false;
	}

	loadLevelInfo();
	SessionController::init();

	this->addChild(level_info[SessionController::curr_level].label);

	initUI(SessionController::curr_level);
	changeLevelUI(SessionController::curr_level);

	updateScoreLabel();

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
void LevelScene::menuStartGameCallback(Ref* sender, Widget::TouchEventType type)
{

	if (type == Widget::TouchEventType::ENDED)
	{

		AudioEngineWrapper::getInstance()->playPressEffect();

		if (!SessionController::isLevelUnlocked(SessionController::curr_level)) {
			return;
		}

		Director::getInstance()->popScene();
		switch (SessionController::curr_level) {
		case 4:
			SessionController::setSpeed(2.0f, true);
			break;
		case 3:
			SessionController::setSpeed(1.3f);
			break;
		case 2:
			SessionController::setSpeed(1.5f);
			break;
		default:
			SessionController::setSpeed(2.0f);
			break;
		}
		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_START, NULL);
	}
}

void LevelScene::menuReturnToMainCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		AudioEngineWrapper::getInstance()->playPressEffect();

		Director::getInstance()->popScene();

		auto main_menu = MenuScene::scene();
		Director::getInstance()->pushScene(main_menu);
	}
}

void LevelScene::menuChangeLevelLeft(Ref* sender, Widget::TouchEventType type) {

	if (type == Widget::TouchEventType::ENDED) {

		SessionController::curr_level--;

		if (SessionController::curr_level < 1) {
			SessionController::curr_level = LEVEL_COUNT;
		}

		auto *left_scene = LevelScene::scene();
		Director::getInstance()->replaceScene(CCTransitionFadeTR::create(0.4, left_scene));
	}
}

void LevelScene::menuChangeLevelRight(Ref* sender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		
		SessionController::curr_level++;

		if (SessionController::curr_level > LEVEL_COUNT) {
			SessionController::curr_level = 1;
		}

		auto *right_scene = LevelScene::scene();

		Director::getInstance()->replaceScene(CCTransitionFadeBL::create(0.4, right_scene));

	}
}

void LevelScene::updateScoreLabel() {
	char s[30];
	sprintf(s, "SCORE: %d", SessionController::getHighScore());
	best_level_score->setString(std::string(s));
}

void LevelScene::menuSwitchAudioCallback(Ref* sender, ui::Widget::TouchEventType type) {

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