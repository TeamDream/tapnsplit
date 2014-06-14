#pragma once
#include "cocos2d.h"
#include "LonelyRect.h"

using namespace cocos2d;
class RectManager
{
public:
	RectManager() {};
	void processClick(Vec2 point);
	int findBoundaryRect();

	Sprite *getRectSprite(int rect_i);
	void deleteRect(int rect_i);
	void addRect(LonelyRect* rect);
	void setBoundary(int _b) { boundary = _b; }
private:
	int boundary;
	std::vector<LonelyRect*> rectPool;
};

