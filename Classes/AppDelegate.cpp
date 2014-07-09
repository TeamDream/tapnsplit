#include "AppDelegate.h"

#include <vector>
#include <string>

#include "MenuScene.h"
#include "GameScene.h"

#include "AppMacros.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Tap and Split");
        director->setOpenGLView(glview);//854õ480
		//glview->setFrameSize(854, 480);
    }

    director->setOpenGLView(glview);

	Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;

	//Simpliest solution. Still need to add other multiresolution option and change policy to NO_BORDER
    searchPath.push_back(mediumResource.directory);
	glview->setDesignResolutionSize(mediumResource.size.width, mediumResource.size.height, ResolutionPolicy::EXACT_FIT);
	director->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
    
    // set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto main_scene = GameScene::scene();

	director->pushScene(main_scene);
    // create a scene. it's an autorelease object
	auto scene = MenuScene::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
