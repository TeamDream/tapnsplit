#include "RectManager.h"
#include "SessionController.h"

void RectManager::processClick(Vec2 point)
{
	std::vector<TouchableRect*>::iterator it = rectPool.begin();
	for (; it != rectPool.end(); it++)
	{
		if ((*it)->containsPoint(point) && !(*it)->isTapped()) { //make it public 
			(*it)->tapIt();//
			SessionController::addScore();
		}
	}
}

int RectManager::findBoundaryRect() {
	std::vector<TouchableRect*>::iterator it = rectPool.begin();
	for (; it != rectPool.end(); it++)
	{
		if ((*it)->getSprite()->getPositionY() + (*it)->getSprite()->getBoundingBox().size.height/2 <= boundary) {
			return static_cast<int>(std::distance(rectPool.begin(), it));
		}
	}

	return -1;
}

Sprite *RectManager::getRectSprite(int rect_i) {
	return rectPool.at(rect_i)->getSprite();
}

bool RectManager::isRectTapped(int rect_i) {
	return rectPool.at(rect_i)->isTapped();
}

void RectManager::deleteRect(int rect_i) {
	rectPool.erase(rectPool.begin() + rect_i);
}

void RectManager::addRect(TouchableRect* rect) {
	rectPool.push_back(rect);
}

int RectManager::getRectCount() {
	return rectPool.size();
}

void RectManager::clearAll() {
	rectPool.clear();
}