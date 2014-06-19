#pragma once
#include "cocos2d.h"
#include "TouchableRect.h"

using namespace cocos2d;
class RectPool
{
public:
	RectPool() {};
	void processClick(Vec2 point);
	int findBoundaryRect();

	Sprite *getRectSprite(int rect_i);
	bool isRectTapped(int rect_i);
	void deleteRect(int rect_i);
	void addRect(TouchableRect* rect);
	void setBoundary(int _b) { boundary = _b; }
	int getBoundary() { return boundary; }
	void clearAll();
	int getRectCount();
private:
	int boundary;
	std::vector<TouchableRect*> rectPool;
};

