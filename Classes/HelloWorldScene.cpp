#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "SessionController.h"

int HelloWorld::count = 0;

int SessionController::current_score = 0;
int SessionController::current_lifes = 3;

Scene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	HelloWorld * layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(ccc4(50, 50, 50, 200))) //RGBA
	{
		return false;
	}

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HelloWorld::onGameStart), GAME_START, NULL);

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
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
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
void HelloWorld::onGameStart(CCObject* obj)
{
    //TODO call startSchedule();

	CCLog("Start game. Need start schedules");

}

void HelloWorld::startSchedule()
{
	this->schedule(schedule_selector(HelloWorld::updateSpeed), 0.2f);
	this->schedule(schedule_selector(HelloWorld::checkRectPositions), 0.033f);
}

void HelloWorld::menuCloseCallback(Ref* sender)
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

void HelloWorld::setCurrSpeed(float  speed) {
	current_speed = speed;
}

float HelloWorld::getCurrSpeed() {
	return current_speed;
}

void HelloWorld::updateSpeed(float  dt) {
	if (count % 5 == 0) {
		if (current_speed > 1.0f) {
			current_speed -= 0.1;
		}
		this->schedule(schedule_selector(HelloWorld::createRandomRect), current_speed / rects_per_h);
	}
}

void HelloWorld::checkRectPositions(float  dt) {
	int lost_rect = rects.findBoundaryRect();

	if (lost_rect >= 0) {
		if (!rects.isRectTapped(lost_rect)) {
			SessionController::damage();
		}

		score_label ->setString(SessionController::getStatus());

		CCSprite *sprite = (CCSprite *)rects.getRectSprite(lost_rect);
		this->removeChild(sprite, true);
		rects.deleteRect(lost_rect);
	}
}


void HelloWorld::createRandomRect(float  dt) {
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

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	CCLog("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	rects.processClick(touch->getLocation());
	return true;
}