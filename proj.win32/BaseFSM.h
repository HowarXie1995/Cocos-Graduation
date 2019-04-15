#ifndef __BaseFSM_h__
#define __BaseFSM_h__

#include <iostream>
#include "cocos2d.h"
#include "BaseRole.h"
#include "propertyManager.h"

USING_NS_CC;

class BaseFSM:public Ref
{
public:
	static BaseFSM * createFSM(BaseRole * baseRole);
	bool init(BaseRole * baseRole);

public:

	void switchMoveState(int dir);	//�ı�״̬�Ľӿ�
	void changeToDefault();		//�л���Ĭ��״̬
	void changeToAttack();		//�л�������״̬
	void changeToLeft();		//��������
	void changeToRight();		//��������
	void changeToDead();		//����״̬

	void changeToEnemy();		//������ƶ�

	//�ͷ�ai
	void purge();

public:
	BaseRole * role;		//Ԥ����BaseRole�ӿ�
};
#endif // !__BaseFSM_h__

