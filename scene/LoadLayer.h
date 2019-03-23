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
	//��ʱ���ص�����
	void onScheduleOnce(float dt);

public:
	//��һ����������ָ�����
	SceneManager * tsm;
};
#endif // !__LoadLayer_h__

