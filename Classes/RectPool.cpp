#include "RectPool.h"
#include "SessionController.h"

void RectPool::processClick(Vec2 point)
{
	std::vector<TouchableRect*>::iterator it = rectPool.begin();
	bool tapped = false;

	for (; it != rectPool.end(); it++)
	{
		if ((*it)->containsPoint(point) && !(*it)->isTapped()) { //make it public 
			(*it)->tapIt();
			tapped = true;
			break;
		}
	}

	if (!tapped) {
		SessionController::damageScore();
	}
}

int RectPool::findBoundaryRect() {
	std::vector<TouchableRect*>::iterator it = rectPool.begin();
 
	for (; it != rectPool.end(); it++)
	{
		int side_pos = (*it)->getSprite()->getPositionY() + (*it)->getSprite()->getBoundingBox().size.height / 2;
		if (side_pos <= boundary) {
			return static_cast<int>(std::distance(rectPool.begin(), it));
		}
	}

	return -1;
}

Sprite *RectPool::getRectSprite(int rect_i) {
	return rectPool.at(rect_i)->getSprite();
}

bool RectPool::isRectTapped(int rect_i) {
	return rectPool.at(rect_i)->isTapped();
}

void RectPool::deleteRect(int rect_i) {
	rectPool.erase(rectPool.begin() + rect_i);
}

void RectPool::addRect(TouchableRect* rect) {
	rectPool.push_back(rect);
}

int RectPool::getRectCount() {
	return rectPool.size();
}

void RectPool::clearAll() {
	rectPool.clear();
}