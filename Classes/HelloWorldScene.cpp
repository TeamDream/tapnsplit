#include "HelloWorldScene.h"
#include "AppMacros.h"

Scene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);
	scene->setColor(ccc3(200, 0, 255));
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

	// add the label as a child to this layer
	this->addChild(label, 1);


	this->schedule(schedule_selector(HelloWorld::createRandomRect), 1.0f);

	return true;
}

void HelloWorld::createRandomRect(float  dt) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("RiseoftheEmpireEra_circle.png");

	// position the sprite on the center of the screen

	float rand_pos = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	int start_pos_x = visibleSize.width * rand_pos;

	sprite->setPosition(Vec2(start_pos_x, 0) + origin);
	sprite->setScale(0.5f);

	auto move = MoveTo::create(4.2f, Vec2(start_pos_x, visibleSize.height));


	sprite->runAction(move);
	// add the sprite as a child to this layer
	this->addChild(sprite);

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
