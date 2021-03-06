#ifndef __LoadLayer_h__
#define __LoadLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;

class LoadLayer:public Layer
{
public:
	CREATE_FUNC(LoadLayer);
	virtual bool init();
	//定时器回调方法
	void onScheduleOnce(float dt);

public:
	//留一个场景管理指针控制
	SceneManager * tsm;
};
#endif // !__LoadLayer_h__

