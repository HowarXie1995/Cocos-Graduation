#ifndef __DialogLayer_h__
#define __DialogLayer_h__
#include <iostream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class DialogLayer:public Layer
{
public:
	//创建对象的方法
	static DialogLayer *createWithJsonFile(const char * filename);

	bool init(std::string str);
	//刷新的函数
	void MultUpdate(float dt);
	//获取数据的方法
	void getDataByIndex(int idx);
	//显示所有文字的方法
	void showAllContent();
	//初始化cocostudio场景的方法
	void initStudioScene(const char * csbFile);
	//点击触发的回调函数
	void touchDownAction(Ref * sender, Widget::TouchEventType controlEvent);
private:
	bool _isOver;		//检查屏幕上的字符串是否显示完全
	int index;			//编号
	
	std::string conversation;		//保留读出来的字符串
	std::vector<std::string> _conVector;	//所有的信息

	Text * speetch;		//保存说话内容
	Text * name;		//保存名字

	std::string mStr;		//用来保存整个字符串
	std::string tempStr;		//用于拼接使用的字符串
	std::vector<std::string>strVector;	//保存字符串的容器
	int vecLength;		//容器的长度
};

#endif // !__DialogLayer_h__
