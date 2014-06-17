#pragma once
#include "cocos2d.h"
#include "TouchableRect.h"

using namespace cocos2d;
class RectManager
{
public:
	RectManager() {};
	void processClick(Vec2 point);
	int findBoundaryRect();

	Sprite *getRectSprite(int rect_i);
	bool isRectTapped(int rect_i);
	void deleteRect(int rect_i);
	void addRect(TouchableRect* rect);
	void setBoundary(int _b) { boundary = _b; }
	void clearAll();
	int getRectCount();
private:
	int boundary;
	std::vector<TouchableRect*> rectPool;
};

