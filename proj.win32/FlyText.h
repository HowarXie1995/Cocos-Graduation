#ifndef __FlyText_h__
#define __FlyText_h__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class FlyText:public Node
{
public:
	static FlyText * create(const char * str);
	bool init(const char *str);
	//播放动画的方法
	void startAnimation();
	//删除对象的方法
	void remove0bject();

private:
	Label * label;

};

#endif // !__FlyText_h__
