#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(Ref* sender);
    
	void createRandomRect(float  dt);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	static int count;
	void updateSpeed(float  dt);

	float getCurrSpeed();
	void setCurrSpeed(float speed);
private:
	float current_speed;
	float rects_per_h;
	int rect_n;

};

#endif // __HELLOWORLD_SCENE_H__
