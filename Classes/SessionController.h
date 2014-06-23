#pragma once

#include "RetryScene.h"

#define GAME_START "Game Start"
#define GAME_END "Game End"

#define HIGHEST_SCORE "score_key"

//controlls current game session - lifes count and riched score
class SessionController {

public:

	static void init() {
		current_score = 0;
		current_lifes = 3;
	}

	static void addScore() {
		++current_score;
	}

	static void damage() {
		//--current_lifes;
		if(isDead()){

			CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_END, NULL);
			Scene *s = RetryScene::scene();
			Director::getInstance()->pushScene(CCTransitionFade::create(0.5,s));
			 
		}
	}

	static bool isDead() { return current_lifes <= 0; }
	static std::string getStatus() {
		char s[50];
		sprintf(s, "Score: %d\n Lifes: %d", current_score, current_lifes);

		return std::string(s);
	
	}

	static int getScore() { return current_score; }

	static void setSpeed(float _level_speed) {
		level_speed = _level_speed;
	}
	static float getSpeed() {
		return level_speed;
	}
private:
	static int current_score;
	static int current_lifes;

	static float level_speed;
};
