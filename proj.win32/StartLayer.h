#ifndef __StartLayer_h__
#define __StartLayer_h__

#include <iostream>
#include "cocos2d.h"


#include "SceneManager.h"
USING_NS_CC;

class StartLayer:public Layer
{
public:

public:
	CREATE_FUNC(StartLayer);
	virtual bool init();
	//��ʱ���ص�����
	void onScheduleOnce(float dt);

public:
	//��һ����������ָ�����
	SceneManager * tsm;
};

#endif
