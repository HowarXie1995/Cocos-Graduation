#ifndef __OperateLayer_h__
#define __OperateLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "tools_define.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

enum BUTTON {
	ATTACK = 101,
	CLOSE,
	PUASE,
	REBACK
};

class OperateLayer:public Layer
{
public:
	CREATE_FUNC(OperateLayer);
	virtual bool init();

	void touchCallBack(Ref * sender, Widget::TouchEventType controlEvent);
};

#endif // !__OperateLayer_h__
