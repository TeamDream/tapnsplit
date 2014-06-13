#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;

int HelloWorld::count = 0;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
	auto background = Sprite::create("background.png");
	layer->setColor(cocos2d::Color3B::WHITE);
    // add layer as a child to scene
	//float background_h = background->boundingBox().size.height;
	//float background_w = background->boundingBox().size.width;

	//float scale_h = scene->getBoundingBox().size.height / background_h;
	//float scale_w = scene->getBoundingBox().size.width / background_w;

	//float scale = scale_h > scale_w ? scale_h : scale_w;
	float scale = 4.0f;
	background->setScale(scale);
	scene->addChild(background);
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	current_speed = 5.f;
	rect_n = 4;
	rects_per_h = 4;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
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
	label->setColor(cocos2d::Color3B::BLACK);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("RiseoftheEmpireEra_circle.png");

 //   // position the sprite on the center of the screen
 //   sprite->setPosition(Vec2(visibleSize / 2) + origin);
	//sprite->setScale(0.5f);

	//auto move = MoveTo::create(4.2f, Vec2(0, 0));

	//sprite->runAction(move);
 //   // add the sprite as a child to this layer
 //   this->addChild(sprite);
 //test schedule

	//setCurrSpeed(1.0f);
	//rect_n = 4;
	//rects_per_h = 1;
	
	
	this->schedule(schedule_selector(HelloWorld::updateSpeed), 1.f);

    return true;
}

void HelloWorld::setCurrSpeed(float  speed) {
	current_speed = speed;
}

float HelloWorld::getCurrSpeed() {
	return current_speed;
}

void HelloWorld::updateSpeed(float  dt) {
	if (count % 3 == 0) {
		if (current_speed > 0.5f) {
			current_speed -= 0.2;
		}
		this->schedule(schedule_selector(HelloWorld::createRandomRect), current_speed / rects_per_h);
	}
}


void HelloWorld::createRandomRect(float  dt) {

	count++;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto sprite = Sprite::create("rect_black.png");
	float sprite_w = sprite->boundingBox().size.width;

	float scale_w = visibleSize.width / sprite_w / rect_n;
	sprite->setScale(scale_w);
	sprite_w = sprite->boundingBox().size.width;

	rects_per_h = visibleSize.height / sprite->boundingBox().size.height;

	int random = rand() % rect_n;
	float hide_h = sprite->boundingBox().size.height / 2;
	int start_pos_x = visibleSize.width - sprite_w * random - sprite_w / 2;

	sprite->setPosition(Vec2(start_pos_x, -hide_h));

	
	auto move = MoveTo::create(current_speed, Vec2(start_pos_x, visibleSize.height + hide_h));

	sprite->runAction(move);

	 
	// add the sprite as a child to this layer
	this->addChild(sprite);

	
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
