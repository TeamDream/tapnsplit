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

		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_PAUSE, NULL);//remove gui window frome game scene
		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_END, NULL);
		auto main_menu = LevelScene::scene();
		Director::getInstance()->pushScene(CCTransitionFade::create(0.5, main_menu));
	}
}

void CompletedWindow::setUpUI() {
	Layout *m_pLayout = dynamic_cast<Layout *> (cocostudio::GUIReader::shareReader()->widgetFromJsonFile("CompleteWindow/CompleteWindow.json"));
	
	auto to_level_menu_btn = dynamic_cast<Button*> (m_pLayout->getChildByName("ToLevelMenu"));
	to_level_menu_btn->addTouchEventListener(CC_CALLBACK_2(CompletedWindow::menuToLevelMenu, this));

	auto continue_btn = dynamic_cast<Button*> (m_pLayout->getChildByName("Continue"));
	continue_btn->addTouchEventListener(CC_CALLBACK_2(CompletedWindow::menuContinueGameCallback, this));

	this->addChild(m_pLayout);
}