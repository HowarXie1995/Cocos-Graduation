#ifndef __MenuLayer_h__
#define __MenuLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;
using namespace cocostudio;

USING_NS_CC;

class MenuLayer:public Layer
{
public:
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	void menuCallBack(Ref * pSender);

public:
	SceneManager * tsm;

};

#endif // !__MenuLayer_h__
