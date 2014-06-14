#pragma once

#include "../class/RetryScene.h"

//controlls current game session - lifes count and riched score
class SessionController{

public:

	static void init() {
		current_score = 0;
		current_lifes = 3;
	}

	static void addScore() {
		++current_score;
	}

	static void damage() {
		--current_lifes;
		if(isDead()){
			Scene *s = RetryScene::scene();
			Director::getInstance()->replaceScene(CCTransitionFade::create(0.5,s));
		}
	}

	static bool isDead() { return current_lifes <= 0; }
	static std::string getStatus() {
		char s[50];
		sprintf(s, "Score: %d\n Lifes: %d", current_score, current_lifes);

		return std::string(s);
	
	}
private:
	static int current_score;
	static int current_lifes;
};
