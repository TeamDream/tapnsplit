#include "AppMacros.h"
#include "CompletedWindow.h"
#include "cocostudio/WidgetReader/WidgetReader.h"
#include "LevelScene.h"
#include "GameScene.h"

using namespace ui;

bool CompletedWindow::init() {
	setUpUI();

	return true;
}

// a selector callback
void CompletedWindow::menuContinueGameCallback(Ref* sender, Widget::TouchEventType type){
	if (type == Widget::TouchEventType::ENDED) {
		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_RESUME, NULL);
	}
}

void CompletedWindow::menuToLevelMenu(Ref* sender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {

		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_RESUME, NULL);//remove gui window frome game scene
		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_END, NULL);
		auto main_menu = LevelScene::scene();
		Director::getInstance()->pushScene(CCTransitionFade::create(0.5, main_menu));
	}
}

void CompletedWindow::setUpUI() {
	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("CompleteWindow/CompleteWindow.json"));
	//manual correction of UI positions. COCOS2dX bug????
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto layout_childs = m_pLayout->getChildren();
	for (auto curr_child = layout_childs.begin(); curr_child != layout_childs.end(); curr_child++) {
		auto wrapped_child = dynamic_cast<Widget*> (*curr_child);
		wrapped_child->setPositionType(Widget::PositionType::ABSOLUTE);
		wrapped_child->setPositionY(origin.y + visibleSize.height*wrapped_child->getPositionPercent().y);
		wrapped_child->setPositionX(origin.x + visibleSize.width*wrapped_child->getPositionPercent().x);
	}

	auto to_level_menu_btn = dynamic_cast<Button*> (m_pLayout->getChildByName("ToLevelMenu"));
	to_level_menu_btn->addTouchEventListener(CC_CALLBACK_2(CompletedWindow::menuToLevelMenu, this));

	auto continue_btn = dynamic_cast<Button*> (m_pLayout->getChildByName("Continue"));
	continue_btn->addTouchEventListener(CC_CALLBACK_2(CompletedWindow::menuContinueGameCallback, this));

	this->addChild(m_pLayout);

	// create and initialize a label "Score Label"
	auto level_name = dynamic_cast<Text*>(m_pLayout->getChildByName("Completed_label"));
	level_name->setFontName("fonts/Impact.ttf");
	level_name->setString("LEVEL ");
	level_name->setFontSize(MIDLE_TITLE_FONT_SIZE);

	auto level_number = LabelTTF::create("COMPLETED!", "fonts/Impact.ttf", MIDLE_TITLE_FONT_SIZE);
	level_number->setColor(Color3B(230, 160, 25));
	level_number->setPosition(level_name->getContentSize().width*2, level_name->getContentSize().height / 2);
	level_name->addChild(level_number);
}