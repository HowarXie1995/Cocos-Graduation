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

	void switchMoveState(int dir);	//改变状态的接口
	void changeToDefault();		//切换到默认状态
	void changeToAttack();		//切换到攻击状态
	void changeToLeft();		//向左行走
	void changeToRight();		//向右行走
	void changeToDead();		//死亡状态

	void changeToEnemy();		//向敌人移动

	//释放ai
	void purge();

public:
	BaseRole * role;		//预留的BaseRole接口
};
#endif // !__BaseFSM_h__

