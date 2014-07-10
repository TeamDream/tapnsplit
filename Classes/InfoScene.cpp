#include "InfoScene.h"
#include "cocostudio/WidgetReader/WidgetReader.h"
#include "AudioEngineWrapper.h"
#include "MenuScene.h"
#include "AppMacros.h"
#include "LevelScene.h"

using namespace ui;

bool InfoScene::init() {
	if (!Layer::init())
	{
		return false;
	}

	setUpUI();


	touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(InfoScene::onTouchBegan2, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(touchListener, -1);

	return true;
}

InfoScene::~InfoScene() { 
	this->getEventDispatcher()->removeEventListener(touchListener); 
}

// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* InfoScene::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	InfoScene * layer = InfoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// a selector callback
void InfoScene::menuToMainCallback(Ref* sender, ui::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {	
		AudioEngineWrapper::getInstance()->playPressEffect();

		Director::getInstance()->popScene();

		auto main_menu = MenuScene::scene();
		Director::getInstance()->pushScene(main_menu);
	}
}

void InfoScene::setUpUI() {

	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("InfoScene/InfoScene.json"));
	m_pLayout->setTag(0);
	this->addChild(m_pLayout);

	auto to_main_menu = dynamic_cast<Button*>(m_pLayout->getChildByName("Menu"));
	to_main_menu->addTouchEventListener(CC_CALLBACK_2(InfoScene::menuToMainCallback, this));

	dynamic_cast<Text *>(m_pLayout->getChildByName("Normal_label"))->setFontName("fonts/Impact.ttf");
	dynamic_cast<Text *>(m_pLayout->getChildByName("Normal_label"))->setFontSize(TITLE_FONT_SIZE);
	dynamic_cast<Text *>(m_pLayout->getChildByName("Life_label"))->setFontName("fonts/Impact.ttf");
	dynamic_cast<Text *>(m_pLayout->getChildByName("Life_label"))->setFontSize(TITLE_FONT_SIZE);
	dynamic_cast<Text *>(m_pLayout->getChildByName("Armor_label"))->setFontName("fonts/Impact.ttf");
	dynamic_cast<Text *>(m_pLayout->getChildByName("Armor_label"))->setFontSize(TITLE_FONT_SIZE);
	dynamic_cast<Text *>(m_pLayout->getChildByName("Death_label"))->setFontName("fonts/Impact.ttf");
	dynamic_cast<Text *>(m_pLayout->getChildByName("Death_label"))->setFontSize(TITLE_FONT_SIZE);
}

bool InfoScene::onTouchBegan2(Touch* touch, Event* event)
{
  
	AudioEngineWrapper::getInstance()->playPressEffect();

	Scene *s = LevelScene::scene();
	Director::getInstance()->replaceScene(CCTransitionCrossFade::create(0.5, s));
	return true;
}
