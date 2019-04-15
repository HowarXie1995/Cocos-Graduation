#include "StartLayer.h"


//把中文转成utf-8格式输出
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32

bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//获得当前屏幕大小
	Get_Screen_winSize;

	//设置一个加载标签
	Label * label = Label::createWithTTF("很久很久以前...",	//标签名字
		"fonts/white.ttf",			//字体
		45);						//字体大小
	label->setPosition(Vec2(winSize.width /2, winSize.height /2));
	this->addChild(label);

	return true;
}
