#include "ControlLayer.h"
#include "MapLayer.h"



//把中文转成utf-8格式输出
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32




bool ControlLayer::init()
{	
	if (!Layer::init())
	{
		return false;
	}
	//把MapLayer添加到ControlLayer上面
	MapLayer * mapLayer = MapLayer::create();
	//执行绑定背景图的方法
	mapLayer->setBackGronud("background.png");
	this->addChild(mapLayer);
	
	return true;
}
