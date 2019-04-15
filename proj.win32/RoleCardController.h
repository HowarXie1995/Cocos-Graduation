#ifndef __RoleCardController_h__
#define __RoleCardController_h__

#include <iostream>
#include <cocos2d.h>
#include "BaseRole.h"
USING_NS_CC;

//单例模式
class RoleCardController:public Ref
{
public:
	static RoleCardController * getInstance();
	bool init();
	void purge();
	
public:
	//容器 标准库容器vector
	std::vector<BaseRole *>heroVec;		//英雄容器
	std::vector<BaseRole *>monsterVec;	//敌人容器

	//可获取到角色ID
	BaseRole * getHero();	
public:
	//变量保存玩家控制的id
	CC_SYNTHESIZE(int, HeroID, HeroID);
};

#endif // __RoleCardController_h__
