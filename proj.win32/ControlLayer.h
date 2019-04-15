#ifndef __ControlLayer_h__
#define __ControlLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "BaseRole.h"
#include "MapLayer.h"
#include "OperateLayer.h"
#include "HRocker.h"
#include "propertyManager.h"
#include "RoleCardController.h"
#include "BaseFSM.h"

USING_NS_CC;


class ControlLayer:public Layer
{
public:
	//�����������Զ��ͷų�
	CREATE_FUNC(ControlLayer);
	//��ʼ��
	virtual bool init();

	void update(float dt);
	void purge();
	//��ʱ���Ļص�����
	void onScheduleOnce(float dt);

public:
	SceneManager * tsm;
	//BaseRole*  hero;
	HRocker * rocker;
	int Level;
};

#endif // !__ControlLayer_h__
