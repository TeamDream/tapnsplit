#pragma once
#include "cocos2d.h"
#include "LonelyRect.h"

using namespace cocos2d;
class RectManager
{
public:
	RectManager(int rectNum);
	void processClick(Vec2 point);

private:
	void istantiateRect();
	void deleteRect();

private:
	std::vector<LonelyRect> rectPool;
};

