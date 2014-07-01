#include "AppDelegate.h"

#include <vector>
#include <string>

#include "MenuScene.h"
#include "GameScene.h"

#include "AppMacros.h"

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
        glview = GLView::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }

    director->setOpenGLView(glview);

	Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
	//if (frameSize.height > mediumResource.size.height)
	//{
 //       searchPath.push_back(largeResource.directory);
	//	glview->setDesignResolutionSize(largeResource.size.width, largeResource.size.height, ResolutionPolicy::NO_BORDER);
 //      // director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	//}
 //   // if the frame's height is larger than the height of small resource size, select medium resource.
 //   else if (frameSize.height > smallResource.size.height)
 //   {
        searchPath.push_back(mediumResource.directory);//as temp solution
		glview->setDesignResolutionSize(mediumResource.size.width, mediumResource.size.height, ResolutionPolicy::EXACT_FIT);
		director->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
 //   }
 //   // if the frame's height is smaller than the height of medium resource size, select small resource.
	//else
 //   {
 //       searchPath.push_back(smallResource.directory);
	//	glview->setDesignResolutionSize(smallResource.size.width, smallResource.size.height, ResolutionPolicy::NO_BORDER);
	//	director->setContentScaleFactor(MIN(smallResource.size.height / frameSize.height, smallResource.size.width / frameSize.width));
 //   }
    
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
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
