#include "GameScene.h"
#include "AppMacros.h"
#include "SessionController.h"

int GameScene::count = 0;

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
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}
	CCLog("GameScene::init()");
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onGameStart), GAME_START, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameScene::onGameEnd), GAME_END, NULL);

	auto background = Sprite::create("background.png");
	float scale = 4.0f;
	background->setScale(scale);
	//	this->addChild(background);

	setUpUI();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::sharedDirector()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

	rects.setBoundary(0);

	return true;
}

void GameScene::setUpUI() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));
	closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// create and initialize a label "Score Label"
	score_label = LabelTTF::create("Score Label", "Arial", TITLE_FONT_SIZE);
	score_label->setPosition(Vec2(origin.x + visibleSize.width / 8,
		origin.y + visibleSize.height - score_label->getContentSize().height));
	score_label->setString(SessionController::getStatus());
	score_label->setZOrder(UIElementsOrder);
	this->addChild(score_label);

}

//Handling event
void GameScene::onGameStart(CCObject* obj)
{
	SessionController::init();
	count = 0;

	for (int i = 0; i < rects.getRectCount(); ++i) {
		CCSprite *sprite = (CCSprite *)rects.getRectSprite(i);
		this->removeChild(sprite, true);
	}

	rects.clearAll();
	current_speed = SessionController::getSpeed();
	time_sec = 0;

	startSchedule();
}

//Handling event
void GameScene::onGameEnd(CCObject* obj)
{
	//unshedule all
	this->unschedule(schedule_selector(GameScene::checkRectPositions));
	this->unschedule(schedule_selector(GameScene::createRandomRect));
	this->unschedule(schedule_selector(GameScene::updateTimer));
}

void GameScene::startSchedule()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float create_rect_speed = (rectFabrik.hide_h*current_speed) / (visibleSize.height + rectFabrik.hide_h);
	
	this->schedule(schedule_selector(GameScene::createRandomRect), create_rect_speed);
	this->schedule(schedule_selector(GameScene::checkRectPositions), 0.033f);	
	this->schedule(schedule_selector(GameScene::updateTimer), 1.f);
}

void GameScene::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)||(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	exit(0);
#endif
}

void GameScene::checkRectPositions(float  dt) {
	int lost_rect = rects.findBoundaryRect();

	if (lost_rect >= 0) {
		if (!rects.isRectTapped(lost_rect)) {
			SessionController::damage();
		}

		CCSprite *sprite = (CCSprite *)rects.getRectSprite(lost_rect);
		this->removeChild(sprite, true);
		rects.deleteRect(lost_rect);
	}

	score_label->setString(SessionController::getStatus());
}


void GameScene::createRandomRect(float  dt) {

	count++;

	if (time_sec % 3 == 0) { //chage rectangle trajectory each 3 sec
		FabrikMode new_mode = static_cast<FabrikMode> (rand() % 3);
		rectFabrik.setMode(new_mode);
	}

	auto new_rect = rectFabrik.createRect();
	new_rect->getSprite()->setZOrder(GameElementsOrder);
	// Create the actions
	FiniteTimeAction* actionMove =
		MoveTo::create(current_speed, Vec2(new_rect->getSprite()->getPositionX(), -rectFabrik.hide_h / 2));
	//actionMove->setTag(0);

	auto speed_act = Speed::create(dynamic_cast<ActionInterval *>(actionMove), 1.0f);
	speed_act->setTag(0);
	new_rect->getSprite()->runAction(speed_act);
	
	rects.addRect(new_rect);
	//speeds.push_back(speed_act);
	this->addChild(new_rect->getSprite());
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	rects.processClick(touch->getLocation());

	return true;
}

void GameScene::updateTimer(float dt) {
	time_sec++;

	if (SessionController::getSpeedChallenge()) {

		if (time_sec % 5 == 0 && current_speed > 0.9f) {

			current_speed /= 1.5f;

			for (int i = 0; i < rects.getRectCount(); i++) {
				auto p = rects.getRectSprite(i);
				auto act = dynamic_cast<Speed *>(p->getActionByTag(0));
				act->setSpeed(1.5);
			}

			auto visibleSize = Director::getInstance()->getVisibleSize();
			float create_rect_speed = (rectFabrik.hide_h*current_speed) / (visibleSize.height + rectFabrik.hide_h);

			this->schedule(schedule_selector(GameScene::createRandomRect), create_rect_speed);



		}
	}

}