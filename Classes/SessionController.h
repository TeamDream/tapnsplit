#pragma once

#include "RetryScene.h"

#define GAME_START "Game Start"
#define GAME_END "Game End"

#define HIGHEST_SCORE "score_key"

//controlls current game session - lifes count and riched score
class SessionController {

public:

	static void init();

	static void addScore();
	static void damage();
	static bool isDead();
	static std::string getScoreStatus();
	static std::string getLifeStatus();

	static int getScore();
	
	//level progress info
	static bool isLevelUnlocked(int level_i);
	static void setLevelUnlocked(int level_i = curr_level + 1);

	static void setHighScore(int score);
	static int getHighScore();

	//2D0: need some refactor here
	static void setSpeed(float _level_speed, bool _speed_challenge = false);
	static float getSpeed();
	static bool getSpeedChallenge();

	static int curr_level;

private:
	static int current_score;
	static int current_lifes;

	static float level_speed;
	static bool speed_challenge;

};
