#ifndef __BaseRole_h__

#define __BaseRole_h__

#include <iostream>
#include "cocos2d.h"
#include "propertyManager.h"
#include "cocostudio/CocoStudio.h"
#include "FlyText.h"


USING_NS_CC;


using namespace cocostudio;

class BaseFSM;
class BaseAI;

typedef enum
{
	TYPE_HERO = 1,
	TYPE_MONSTER = 2,
}ROLE_TYPE;

typedef enum      //保存角色的状态
{
	ROLE_DEFAULT = 1,
	ROLE_ATTACK,
	ROLE_MOVE,
	ROLE_DEAD,
	ROLE_FREE,		//释放状态
}ROLE_STATE;

typedef enum    //保存角色脸朝向
{
	FACE_LEFT,
	FACE_RIGHT,
}ROLE_FACE;

class BaseRole:public Node
{
public:
	static BaseRole * createWithProperty(propertyManager * manager);
	bool init(propertyManager * manager);
public:
	//改变脸朝向的方法
	void changeFace(ROLE_FACE face);
	virtual void draw(cocos2d::Renderer * renderer, \
		const cocos2d::Mat4&transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
	//回调函数:变为默认状态
	void animationEvent(Armature * pArmature, MovementEventType movementType, 
			const std::string & movementIDstr);
	//获得碰撞检测的矩形区
	Rect getRealRect(BaseRole * role, Rect rect);
	void fallHP(const char *hpCount);
	//释放的方法
	void purge();
public:
	BaseRole * lockRole;		//索敌对象
	propertyManager * property;
	//保存变量
	ROLE_TYPE type;
	ROLE_STATE state;
	ROLE_FACE face;

	//创建角色动画的对象
	CC_SYNTHESIZE(Armature *, armature, Armature);
	CC_SYNTHESIZE(BaseFSM *, baseFSM, BaseFSM);
	CC_SYNTHESIZE(BaseAI *, baseAI, BaseAI);

};

#endif // !__BaseRole_h__
