#ifndef __ControlLayer_h__
#define __ControlLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;


class ControlLayer:public Layer
{
public:
	//�����������Զ��ͷų�
	CREATE_FUNC(ControlLayer);
	//��ʼ��
	virtual bool init();

public:
	SceneManager * tsm;
};

#endif // !__ControlLayer_h__
