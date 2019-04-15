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
	//���Ŷ����ķ���
	void startAnimation();
	//ɾ������ķ���
	void remove0bject();

private:
	Label * label;

};

#endif // !__FlyText_h__
