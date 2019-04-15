#ifndef __BaseAI_h__
#define __BaseAI_h__

#include <iostream>
#include "cocos2d.h"
#include "BaseRole.h"

USING_NS_CC;

class BaseAI:public Ref
{
public:
	//创建AI的方法
	static BaseAI * createAI(BaseRole * role);
	//初始化AI的方法
	bool init(BaseRole * role);
	//启动AI的方法
	void startRoleAI();
	//停止AI的方法
	void stopRoleAI();
	//更新AI的方法
	void updateFunc(float dt);
	//释放AI的方法
	void purge();
public:
	BaseRole * baseRole;
	int NumBaseRole;

};

#endif // !__BaseAI_h__
