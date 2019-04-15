#ifndef __BaseAI_h__
#define __BaseAI_h__

#include <iostream>
#include "cocos2d.h"
#include "BaseRole.h"

USING_NS_CC;

class BaseAI:public Ref
{
public:
	//����AI�ķ���
	static BaseAI * createAI(BaseRole * role);
	//��ʼ��AI�ķ���
	bool init(BaseRole * role);
	//����AI�ķ���
	void startRoleAI();
	//ֹͣAI�ķ���
	void stopRoleAI();
	//����AI�ķ���
	void updateFunc(float dt);
	//�ͷ�AI�ķ���
	void purge();
public:
	BaseRole * baseRole;
	int NumBaseRole;

};

#endif // !__BaseAI_h__
