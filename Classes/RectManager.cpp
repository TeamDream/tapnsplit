#include "RectManager.h"

void RectManager::processClick(Vec2 point)
{
	std::vector<LonelyRect>::iterator it = rectPool.begin();
	for ( ; it != rectPool.end(); it++)
	{
		//if(it->containsPoint(point)) //make it public 
			;//it->tapIt()
	}
}