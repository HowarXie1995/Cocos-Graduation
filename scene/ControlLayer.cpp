#include "ControlLayer.h"
#include "MapLayer.h"



//������ת��utf-8��ʽ���
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32




bool ControlLayer::init()
{	
	if (!Layer::init())
	{
		return false;
	}
	//��MapLayer��ӵ�ControlLayer����
	MapLayer * mapLayer = MapLayer::create();
	//ִ�а󶨱���ͼ�ķ���
	mapLayer->setBackGronud("background.png");
	this->addChild(mapLayer);
	
	return true;
}
