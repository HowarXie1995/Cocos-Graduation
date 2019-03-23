#ifndef __tools_define_h__
#define __tools_define_h__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
/*
宏：获取屏幕大小位置
单位：Size
用法：width  //宽度
	  length //长度
*/
#define Get_Screen_winSize  Size winSize = Director::getInstance()->getVisibleSize()


#endif // !__tools_define_h__
