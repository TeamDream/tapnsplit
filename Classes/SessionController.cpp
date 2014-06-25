#include "SessionController.h"

int SessionController::curr_level = 1;

void SessionController::init() {
	current_score = 0;
	current_lifes = 3;

	setLevelUnlocked(1);//first level always unlocked
	setLevelUnlocked(4);// -//-
}

void SessionController::addScore() {
	++current_score;
}

void SessionController::damage() {
	--current_lifes;
	if (isDead()){

		CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_END, NULL);
		Scene *s = RetryScene::scene();
		Director::getInstance()->pushScene(CCTransitionFade::create(0.5, s));
	}
}

bool SessionController::isDead() { 
	return current_lifes <= 0; 
}
std::string SessionController::getStatus() {
	char s[50];
	sprintf(s, "Score: %d\n Lifes: %d", current_score, current_lifes);

	return std::string(s);

}

int SessionController::getScore() { return current_score; }

//2D0: need some refactor here
void SessionController::setSpeed(float _level_speed, bool _speed_challenge) {
	level_speed = _level_speed;
	speed_challenge = _speed_challenge;
}

float SessionController::getSpeed() {
	return level_speed;
}

bool SessionController::getSpeedChallenge() {
	return speed_challenge;
}

bool SessionController::isLevelUnlocked(int level_i) {
	
	char s[50];
	sprintf(s, "LEVEL_%d_STATUS", level_i);

	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	bool level_completed = def->getBoolForKey(s);
	 
	return level_completed;
}
void SessionController::setLevelUnlocked(int level_i) {

	char s[50];
	sprintf(s, "LEVEL_%d_STATUS", level_i);

	CCUserDefault *def = CCUserDefault::sharedUserDefault();
	def->setBoolForKey(s, true);
}