#include "SimpleAudioEngine.h"


//maybe there it can be rewrited by "Observer" pattern

class AudioEngineWrapper {

public:

	static AudioEngineWrapper* getInstance() {
		static AudioEngineWrapper* instance = new AudioEngineWrapper();
		return instance;
	}

	void playRandomTrack() {

		if (!isSoundEnabled()) {
			return;
		}
		char* track = getRandomTrack();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			track, true);

	}

	void playStartSong() {

		if (!isSoundEnabled()) {
			return;
		}

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			"background_m.mp3", true);
	}

	void playPressEffect() {

		if (!isSoundEnabled()) {
			return;
		}

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
			"press.wav");
	}

	void playGameOver() {

		if (!isSoundEnabled()) {
			return;
		}

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
			"gameover.mp3");
	}

	void turnVolumeOff(bool _off) {
		if (_off) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		}
		else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		}

		setSoundEnabled(!_off);
	}

	inline bool isSoundEnabled() {
		return sound_enabled;
	}

	inline void setSoundEnabled(bool _enabled) {
		sound_enabled = _enabled;
	}

private:

	AudioEngineWrapper() {
		sound_enabled = true;

		songs.push_back("tiger.mp3");
		songs.push_back("1.mp3");
		songs.push_back("background_m.mp3");
		songs.push_back("stronger.mp3");
		songs.push_back("lucky.mp3");
		songs.push_back("throne.mp3");

	};

	char* getRandomTrack() {
	
		int random = rand() % songs.size();
		char* music = songs.at(random);

		return music;
	}

	bool sound_enabled;
	std::vector <char *> songs;

};