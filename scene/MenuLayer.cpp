#include "MenuLayer.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32



bool MenuLayer::init()
{
	//Node * node = CSLoader::createNode("");	//可直接添加scene的控件运行场景界面

	//this->addChild(node);
	if (!Layer::init())
	{
		return false;
	}
	//1、获取窗口大小
	Get_Screen_winSize;
	//2、添加一个标签
	Label * label = Label::createWithTTF("黑夜",
		"fonts/white.ttf",
		48);
	/*可调节颜色*/
	//label->setColor(Color3B(255, 0, 0));
	label->setPosition(Vec2(winSize.width / 2, winSize.height * 3 / 4));
	this->addChild(label);
	//3、创建一个文字按钮
	/*开始按钮*/
	MenuItemLabel * menuItem = MenuItemLabel::create(Label::createWithTTF("开始", "fonts/white.ttf", 30),
		CC_CALLBACK_1(MenuLayer::menuCallBack, this));
	//给menuItem设置一个Tag
	menuItem->setTag(101);
	menuItem->setPosition(Vec2(winSize.width / 2, winSize.height * 0.3));
	/*结束按钮*/
	MenuItemLabel * menuItem_2 = MenuItemLabel::create(Label::createWithTTF("结束", "fonts/white.ttf", 30),
		CC_CALLBACK_1(MenuLayer::menuCallBack, this));
	//给menuItem设置一个Tag
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width / 2, winSize.height * 0.15));

	//创建菜单对象
	auto menu = Menu::create(menuItem, menuItem_2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

//按钮回调函数
//需要区分
void MenuLayer::menuCallBack(Ref * pSender)
{
	//1、按钮转换
	switch (((MenuItem *)pSender)->getTag())
	{
		case 101:		//开始按钮
		{
			tsm->goGameScene();
		}
		break;
		case 102:		//退出按钮
		{
			Director::getInstance()->end();
			exit(0);
		}
		break;
		default:
			break;
	}


}
