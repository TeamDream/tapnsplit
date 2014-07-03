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
	};

	char* getRandomTrack() {
		int sounds_n = 6;
		int random = rand() % sounds_n;
		char* music;

		switch (random) {
		case 0:
			music = "tiger.mp3";
			break;
		case 1:
			music = "1.mp3";
			break;
		case 2:
			music = "background_m.mp3";
			break;
		case 3:
			music = "stronger.mp3";
			break;
		case 4:
			music = "lucky.mp3";
			break;
		case 5:
			music = "throne.mp3";
			break;
		}

		return music;
	}

	bool sound_enabled;

};