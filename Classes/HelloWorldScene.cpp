#include "HelloWorldScene.h"
#include "AppMacros.h"

int HelloWorld::count = 0;

Scene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	HelloWorld * layer = HelloWorld::create();
	
    // add layer as a child to scene
	//float background_h = background->boundingBox().size.height;
	//float background_w = background->boundingBox().size.width;

	//float scale_h = scene->getBoundingBox().size.height / background_h;
	//float scale_w = scene->getBoundingBox().size.width / background_w;

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
	if (!LayerColor::initWithColor(ccc4(200, 200, 200, 200))) //RGBA
	{
		return false;
	}

	auto background = Sprite::create("background.png");
	float scale = 4.0f;
	background->setScale(scale);
	this->addChild(background);

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

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	
	
	current_speed = 5.f;
	rect_n = 4;
	rects_per_h = 4;
	this->schedule(schedule_selector(HelloWorld::updateSpeed), 0.1f);

	return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
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
		if (current_speed > 0.9f) {
			current_speed -= 0.05;
		}
		this->schedule(schedule_selector(HelloWorld::createRandomRect), current_speed / rects_per_h);
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

	float hide_h = new_rect->getSprite()->boundingBox().size.height / 2;

	rects_per_h = visibleSize.height / new_rect->getSprite()->boundingBox().size.height;

	int random = rand() % rect_n;

	int start_pos_x = /*visibleSize.width -*/ sprite_w * random + sprite_w / 2;

	new_rect->getSprite()->setPosition(Vec2(start_pos_x, visibleSize.width + hide_h));

	 // Create the actions
    CCFiniteTimeAction* actionMove = 
		CCMoveTo::create(current_speed, Vec2(start_pos_x, -hide_h));
    CCFiniteTimeAction* actionMoveDone = 
        CCCallFuncN::create( this, 
        callfuncN_selector(HelloWorld::spriteMoveFinished));
    new_rect->getSprite()->runAction( CCSequence::create(actionMove, 
        actionMoveDone, NULL) );

	new_rect->tapIt();

	this->addChild(new_rect->getSprite());
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
  CCSprite *sprite = (CCSprite *)sender;
  this->removeChild(sprite, true);

  CCLog("Sprite move finished");
}

bool HelloWorld::clickOnRect(Vec2 clickPos)
{
	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	CCLog("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	if (clickOnRect(touch->getLocation()))
		;//doSomething();
	else
		;//doSomethingElse();
	return true;
}