#pragma once
#include "cocos2d.h"
#include "TouchableRect.h"

using namespace cocos2d;
class RectPool
{
public:
	RectPool() {};
	//send current click through all rects
	void processClick(Vec2 point);
	//get rect behind the level boundary. Return -1 otherwise 
	int findBoundaryRect();

	Sprite *getRectSprite(int rect_i);
	bool isRectTapped(int rect_i);
	
	void deleteRect(int rect_i);
	void addRect(TouchableRect* rect);

	int getRectCount();
	void clearAll();
	
	int boundary;

	std::vector<TouchableRect*> rectPool;
};

