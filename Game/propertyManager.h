#ifndef __propertyManager_h__
#define __propertyManager_h__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class propertyManager:public Ref
{
public:
	CREATE_FUNC(propertyManager);
	virtual bool init();

public:
	//快速创建一个成员变量，并生成一个set方法和get方法
	CC_SYNTHESIZE(int, ID, ID);		//角色ID
	CC_SYNTHESIZE(int, HP, HP);		//角色血量
	CC_SYNTHESIZE(int, ATK, ATK);	//角色攻击力
	CC_SYNTHESIZE(unsigned int, LockLimit, LockLimit);	//索地区
	CC_SYNTHESIZE(unsigned int, ATKLimit, ATKLimit);	//攻击区

	CC_SYNTHESIZE(std::string, ArmatureName, ArmatureName);	//动画资源路径的保存
	CC_SYNTHESIZE(std::string, DataName, DataName);			//动画名字的保存
	CC_SYNTHESIZE(std::string, PlayerName, PlayerName);		//角色名字的保存
	
	CC_SYNTHESIZE(Rect, HitRect, HitRect);			//攻击框
	CC_SYNTHESIZE(Point, HitPoint, HitPoint);		//攻击框起始点坐标

	CC_SYNTHESIZE(Rect, GetHitRect, GetHitRect);			//攻击框
	CC_SYNTHESIZE(Point, GetHitPoint, GetHitPoint);		//攻击框起始点坐标

};

#endif // !__propertyManager_h__
