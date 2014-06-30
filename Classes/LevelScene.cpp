#include "LevelScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SessionController.h"
#include "AppMacros.h"
#include "cocostudio/WidgetReader/WidgetReader.h"

using namespace ui;

void LevelScene::loadLevelInfo() {


	LevelInfo curr;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Arial", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setString("Level 1");
	curr.label->setZOrder(UIElementsOrder);
	curr.label->retain();

	curr.background = Sprite::create("NewSprites/tapIt_levelsScreen_1_background.png");
	curr.background->setPosition(Vec2(origin + visibleSize / 2));
	curr.background->setZOrder(BackgroundOrder);
	curr.background->retain();
	

	level_info[1] = curr;

	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Arial", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setString("Level 2");
	curr.label->setZOrder(UIElementsOrder);

	curr.background = Sprite::create("NewSprites/tapIt_levelsScreen_1_background.png");
	curr.background->setPosition(Vec2(origin + visibleSize / 2));
	curr.background->setZOrder(BackgroundOrder);
	curr.background->retain();
	curr.label->retain();

	level_info[2] = curr;


	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Arial", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setZOrder(UIElementsOrder);
	curr.label->setString("Level 3");
	curr.background = Sprite::create("NewSprites/tapIt_levelsScreen_1_background.png");
	curr.background->setPosition(Vec2(origin + visibleSize / 2));
	curr.background->setZOrder(BackgroundOrder);
	curr.background->retain();
	curr.label->retain();

	level_info[3] = curr;

	// create and initialize a label "Score Label"
	curr.label = LabelTTF::create("Level Label", "Arial", TITLE_FONT_SIZE);
	curr.label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - curr.label->getContentSize().height));
	curr.label->setZOrder(UIElementsOrder);
	curr.label->setString("Level 4");
	curr.background = Sprite::create("NewSprites/tapIt_levelsScreen_1_background.png");
	curr.background->setPosition(Vec2(origin + visibleSize / 2));
	curr.background->setZOrder(BackgroundOrder);
	curr.background->retain();
	curr.label->retain();

	level_info[4] = curr;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool LevelScene::init() {

	if (!Layer::init()) //RGBA
	{
		return false;
	}

	loadLevelInfo();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->addChild(level_info[SessionController::curr_level].background);
	this->addChild(level_info[SessionController::curr_level].label);

	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("LevelScene/LevelScene.json"));
	this->addChild(m_pLayout);

	Button* start_game = dynamic_cast<Button*>(m_pLayout->getChildByName("Play"));
	start_game->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuStartGameCallback, this));
	Button* move_left = dynamic_cast<Button*>(m_pLayout->getChildByName("MoveLeft"));
	move_left->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuChangeLevelLeft, this));
	Button* move_right = dynamic_cast<Button*>(m_pLayout->getChildByName("MoveRight"));
	move_right->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuChangeLevelRight, this));
	Button* to_main_menu = dynamic_cast<Button*>(m_pLayout->getChildByName("Menu"));
	to_main_menu->addTouchEventListener(CC_CALLBACK_2(LevelScene::menuReturnToMainCallback, this));

	best_level_score = dynamic_cast<Text*>(m_pLayout->getChildByName("Score"));
	
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

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
			"press.wav");

		if (!SessionController::isLevelUnlocked(SessionController::curr_level)) {
			return;
		}

		Director::getInstance()->popScene();
		switch (SessionController::curr_level) {
		case 4:
			SessionController::setSpeed(2.0f, true);
			break;
		case 3:
			SessionController::setSpeed(0.9f);
			break;
		case 2:
			SessionController::setSpeed(1.0f);
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
		Director::getInstance()->popScene();

		auto main_menu = MenuScene::scene();
		Director::getInstance()->pushScene(main_menu);
	}
}

void LevelScene::menuChangeLevelLeft(Ref* sender, Widget::TouchEventType type) {

	if (type == Widget::TouchEventType::ENDED) {

		this->removeChild(level_info[SessionController::curr_level].background);
		this->removeChild(level_info[SessionController::curr_level].label);

		SessionController::curr_level--;

		if (SessionController::curr_level < 1) {
			SessionController::curr_level = LEVEL_COUNT;
		}

		this->addChild(level_info[SessionController::curr_level].background);
		this->addChild(level_info[SessionController::curr_level].label);

		updateScoreLabel();
	}
}

void LevelScene::menuChangeLevelRight(Ref* sender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		this->removeChild(level_info[SessionController::curr_level].background);
		this->removeChild(level_info[SessionController::curr_level].label);

		SessionController::curr_level++;

		if (SessionController::curr_level > LEVEL_COUNT) {
			SessionController::curr_level = 1;
		}

		this->addChild(level_info[SessionController::curr_level].background);
		this->addChild(level_info[SessionController::curr_level].label);

		updateScoreLabel();
	}
}

void LevelScene::updateScoreLabel() {
	char s[30];
	sprintf(s, "SCORE: %d", SessionController::getHighScore());
	best_level_score->setString(std::string(s));
}