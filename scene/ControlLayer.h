#ifndef __ControlLayer_h__
#define __ControlLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;


class ControlLayer:public Layer
{
public:
	//创建并加入自动释放池
	CREATE_FUNC(ControlLayer);
	//初始化
	virtual bool init();

public:
	SceneManager * tsm;
};

#endif // !__ControlLayer_h__
