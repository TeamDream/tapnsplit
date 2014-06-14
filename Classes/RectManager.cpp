#include "RectManager.h"

void RectManager::processClick(Vec2 point)
{
	std::vector<LonelyRect*>::iterator it = rectPool.begin();
	for (; it != rectPool.end(); it++)
	{
		if ((*it)->containsPoint(point)) //make it public 
			(*it)->tapIt();//
	}
}

int RectManager::findBoundaryRect() {
	std::vector<LonelyRect*>::iterator it = rectPool.begin();
	for (; it != rectPool.end(); it++)
	{
		if ((*it)->getSprite()->getPositionY() >= boundary) {
			return static_cast<int>(std::distance(rectPool.begin(), it));
		}
	}

	return -1;
}

Sprite *RectManager::getRectSprite(int rect_i) {
	return rectPool.at(rect_i)->getSprite();
}

void RectManager::deleteRect(int rect_i) {
	rectPool.erase(rectPool.begin() + rect_i);
}

void RectManager::addRect(LonelyRect* rect) {
	rectPool.push_back(rect);
}