#include "DialogLayer.h"

DialogLayer *DialogLayer::createWithJsonFile(const char * filename)
{
	DialogLayer * dialogLayer = new DialogLayer();
	if (dialogLayer && dialogLayer->init(filename))
	{
		dialogLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(dialogLayer);
	}
	return dialogLayer;
}

bool DialogLayer::init(std::string str)
{
	//��ʾ���浽��Ļ��
	return true;
}

void DialogLayer::MultUpdate(float dt)
{
}

void DialogLayer::getDataByIndex(int idx)
{
}

void DialogLayer::showAllContent()
{
}

void DialogLayer::initStudioScene(const char * csbFile)
{
}

void DialogLayer::touchDownAction(Ref * sender, Widget::TouchEventType controlEvent)
{
}
