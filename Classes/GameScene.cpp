#include "GameScene.h"
#include "AppMacros.h"
#include "SessionController.h"
#include "cocostudio/WidgetReader/WidgetReader.h"
#include "CompletedWindow.h"
#include "MenuScene.h"

using namespace ui;

int SessionController::current_score = 0;
int SessionController::current_lifes = 3;
float SessionController::level_speed = 4.0f;
bool SessionController::speed_challenge = false;

Scene* GameScene::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	GameScene * layer = GameScene::create();
 
	// add layer as a child to scene
	scene->addChild(layer,100);
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	
	if (!Layer::init()) //RGBA
	{
		return false;
	}

	CCLog("GameScene::init()");
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onGameStart), GAME_START, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onGameEnd), GAME_END, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onGamePause), GAME_PAUSE, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onGameResume), GAME_RESUME, NULL);

	//setUpBackground();
	setUpUI();

	rects.boundary = 0;
	is_playing = false;

	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

void GameScene::setUpUI() {
	//Can't add it as child to 'this' because of event overlapping 
	auto m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("GameplayScene/GameplayScene.json"));

	//Just get if from saved resources:
	auto to_main_menu = dynamic_cast<Button*>((m_pLayout->getChildByName("Menu"))->clone());
	to_main_menu->addTouchEventListener(CC_CALLBACK_2(GameScene::menuReturnToMainCallback, this));
	to_main_menu->setZOrder(UIElementsOrder);
	this->addChild(to_main_menu);
	
	auto life_logo = dynamic_cast<ImageView*>((m_pLayout->getChildByName("LifesLogo"))->clone());
	life_logo->setZOrder(UIElementsOrder);
	this->addChild(life_logo);
	
	auto score_logo = dynamic_cast<ImageView*>((m_pLayout->getChildByName("ScoreLogo"))->clone());
	score_logo->setZOrder(UIElementsOrder);
	this->addChild(score_logo);
	
	life_label = dynamic_cast<Text*>((m_pLayout->getChildByName("LifesLabel"))->clone());
	life_label->setZOrder(UIElementsOrder);
	life_label->setFontName("fonts/Myriad Pro.ttf");
	this->addChild(life_label);
	
	score_label = dynamic_cast<Text*>((m_pLayout->getChildByName("ScoreLabel"))->clone());
	score_label->setZOrder(UIElementsOrder);
	score_label->setFontName("fonts/Myriad Pro.ttf");
	this->addChild(score_label);

	//set complete level window
	completed_gui = CompletedWindow::create();
	completed_gui->setZOrder(10);
	completed_gui->setVisible(false);
	this->addChild(completed_gui);
}

void GameScene::setUpBackground() {

	this->removeChildByTag(666);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	char level_s[50];
	sprintf(level_s, "GAMEPLAY/level%d/gameplay%d_background.png", SessionController::curr_level, SessionController::curr_level);

	auto background = Sprite::create(level_s);
	background->setPosition(Vec2(origin + visibleSize / 2));
	background->setZOrder(BackgroundOrder);
	background->setTag(666);
	this->addChild(background);
}

//Handling event
void GameScene::onGameStart(CCObject* obj)
{
	SessionController::init();

	for (int i = 0; i < rects.getRectCount(); ++i) {
		CCSprite *sprite = (CCSprite *)rects.getRectSprite(i);
		this->removeChild(sprite, true);
	}

	setUpBackground();

	rects.clearAll();
	current_speed = SessionController::getSpeed();
	time_sec = 0;

	startSchedule();
	updateLabels();

	is_playing = true;
}

//Handling event
void GameScene::onGameEnd(CCObject* obj)
{
	//unshedule all
	this->unschedule(schedule_selector(GameScene::checkRectPositions));
	this->unschedule(schedule_selector(GameScene::createRandomRect));
	this->unschedule(schedule_selector(GameScene::updateTimer));

	is_playing = false;

	SessionController::updateScores();
}

void GameScene::onGamePause(CCObject* obj) {
	
	this->pauseSchedulerAndActions();
	this->setTouchEnabled(false);

	for (int i = 0; i < rects.getRectCount(); i++) {
		rects.getRectSprite(i)->pauseSchedulerAndActions();
		rects.getRectSprite(i)->setColor(Color3B(100, 100, 100));
	}
	
	auto backgr = this->getChildByTag(666);
	backgr->setColor(Color3B(100, 100, 100));

	completed_gui->setVisible(true);
}

void GameScene::onGameResume(CCObject* obj) {
	this->resumeSchedulerAndActions();
	this->setTouchEnabled(true);

	for (int i = 0; i < rects.getRectCount(); i++) {
		rects.getRectSprite(i)->resumeSchedulerAndActions();
		rects.getRectSprite(i)->setColor(Color3B(255, 255, 255));
	}
	auto backgr = this->getChildByTag(666);
	backgr->setColor(Color3B(255, 255, 255));

	completed_gui->setVisible(false);
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if (is_playing) {
		rects.processClick(touch->getLocation());
		updateLabels();

		checkScoreProgress();
	}

	return true;
}


void GameScene::startSchedule()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float create_rect_speed = (rectFabrik.hide_h*current_speed) / (visibleSize.height + rectFabrik.hide_h);
	
	this->schedule(schedule_selector(GameScene::createRandomRect), create_rect_speed);
	this->schedule(schedule_selector(GameScene::checkRectPositions), 0.033f);	
	this->schedule(schedule_selector(GameScene::updateTimer), 1.f);
}

void GameScene::checkRectPositions(float  dt) {

	int lost_rect = rects.findBoundaryRect();

	if (lost_rect >= 0) {
		if (!rects.isRectTapped(lost_rect)) {
			rects.rectPool.at(lost_rect)->dieAction();
		}

		CCSprite *sprite = (CCSprite *)rects.getRectSprite(lost_rect);
		this->removeChild(sprite, true);
		rects.deleteRect(lost_rect);
	}
}


void GameScene::createRandomRect(float  dt) {

	if (time_sec % 3 == 0) { //chage rectangle trajectory each 3 sec
		FabrikMode new_mode = static_cast<FabrikMode> (rand() % 3);
		rectFabrik.setMode(new_mode);
	}

	auto new_rect = rectFabrik.createRect();
	new_rect->getSprite()->setZOrder(GameElementsOrder);
	// Create the action
	FiniteTimeAction* actionMove =
		MoveTo::create(current_speed, Vec2(new_rect->getSprite()->getPositionX(), -rectFabrik.hide_h));
	//Wrap it to speed action
	auto speed_act = Speed::create(dynamic_cast<ActionInterval *>(actionMove), 1.0f);
	speed_act->setTag(0);
	new_rect->getSprite()->runAction(speed_act);
	
	rects.addRect(new_rect);
	this->addChild(new_rect->getSprite());
}

void GameScene::updateTimer(float dt) {

	time_sec++;

	updateLabels();

	if (SessionController::getSpeedChallenge()) {

		if (time_sec % 5 == 0 && current_speed > 1.1f) {

			current_speed /= 1.2f;

			for (int i = 0; i < rects.getRectCount(); i++) {
				auto p = rects.getRectSprite(i);
				auto act = dynamic_cast<Speed *>(p->getActionByTag(0));
				act->setSpeed(1.2);
			}

			auto visibleSize = Director::getInstance()->getVisibleSize();
			float create_rect_speed = (rectFabrik.hide_h*current_speed) / (visibleSize.height + rectFabrik.hide_h);

			this->schedule(schedule_selector(GameScene::createRandomRect), create_rect_speed);
		}
	}
 
}

void GameScene::checkScoreProgress() {

	int next_level_i = SessionController::curr_level + 1; //1,2,3,4
	if (next_level_i > 4) {
		next_level_i = 1;
	}

	if (SessionController::getScore() == 5 && !SessionController::isLevelUnlocked(next_level_i)) {
		//finish screen
		SessionController::setLevelUnlocked();
		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_PAUSE, NULL);
	}
}

void GameScene::updateLabels() {
	score_label->setString(SessionController::getScoreStatus());
	life_label->setString(SessionController::getLifeStatus());
}

void GameScene::menuReturnToMainCallback(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {

		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_END, NULL);
		auto main_menu = MenuScene::scene();
		Director::getInstance()->pushScene(CCTransitionFade::create(0.5, main_menu));
	}
}
