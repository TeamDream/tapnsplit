#include "GameScene.h"
#include "AppMacros.h"
#include "SessionController.h"

int GameScene::count = 0;

int SessionController::current_score = 0;
int SessionController::current_lifes = 3;

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

	auto background = Sprite::create("background.png");
	float scale = 4.0f;
	background->setScale(scale);
	//this->addChild(background);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::sharedDirector()->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, 100);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	score_label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	score_label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - score_label->getContentSize().height));
	score_label->setString(SessionController::getStatus());
	this->addChild(score_label);
	current_speed = 5.f;
	rect_n = 4;
	rects_per_h = 4;
	startSchedule();

	rects.setBoundary(visibleSize.height);

	return true;
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
	current_speed = 5.f;

}

void GameScene::startSchedule()
{
	this->schedule(schedule_selector(GameScene::updateSpeed), 0.2f);
	this->schedule(schedule_selector(GameScene::checkRectPositions), 0.033f);
}

void GameScene::menuCloseCallback(Ref* sender)
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

void GameScene::setCurrSpeed(float  speed) {
	current_speed = speed;
}

float GameScene::getCurrSpeed() {
	return current_speed;
}

void GameScene::updateSpeed(float  dt) {


	if (count % 5 == 0) {
		if (current_speed > 1.0f) {
			current_speed -= 0.1;
		}
		CCLog("createRandomRect updated!");
		this->schedule(schedule_selector(GameScene::createRandomRect), current_speed / rects_per_h);

	}
}

void GameScene::checkRectPositions(float  dt) {
	int lost_rect = rects.findBoundaryRect();

	if (lost_rect >= 0) {
		if (!rects.isRectTapped(lost_rect)) {
			SessionController::damage();
		}

		score_label->setString(SessionController::getStatus());

		CCSprite *sprite = (CCSprite *)rects.getRectSprite(lost_rect);
		this->removeChild(sprite, true);
		rects.deleteRect(lost_rect);
	}
}


void GameScene::createRandomRect(float  dt) {


	count++;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto new_rect = new LonelyRect("rect_black.png");
	float sprite_w = new_rect->getSprite()->boundingBox().size.width;

	float scale_w = visibleSize.width / sprite_w / rect_n;
	new_rect->getSprite()->setScale(scale_w);
	sprite_w = new_rect->getSprite()->boundingBox().size.width;

	rects_per_h = visibleSize.height / new_rect->getSprite()->boundingBox().size.height;

	int random = rand() % rect_n;
	float hide_h = new_rect->getSprite()->boundingBox().size.height / 2;
	int start_pos_x = visibleSize.width - sprite_w * random - sprite_w / 2;

	new_rect->getSprite()->setPosition(Vec2(start_pos_x, -hide_h));

	// Create the actions
	CCFiniteTimeAction* actionMove =
		CCMoveTo::create(current_speed, Vec2(start_pos_x, visibleSize.height + hide_h));
	new_rect->getSprite()->runAction(actionMove);

	rects.addRect(new_rect);

	this->addChild(new_rect->getSprite());
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	rects.processClick(touch->getLocation());
	return true;
}