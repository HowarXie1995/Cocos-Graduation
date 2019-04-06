#ifndef __BaseRole_h__

#define __BaseRole_h__

#include <iostream>
#include "cocos2d.h"
#include "propertyManager.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
			/*主角参数定义*/
#define  ROLE_NAME	"hero"
#define  ROLE_DATA	"hero/hero.Exportjson"
#define  ROLE_ATK	 1000 	 
#define  ROLE_ATKLIMIT   100
#define  ROLE_HP	 10000
#define  ROLE_ID	1
#define  ROLE_LOCKLIMIT 400
#define	 ROLE_PLAYER_NAME "英雄"
#define  ROLE_HITRECT	{{40,-40},{80,80}}
#define  ROLE_GETHITRECT  {{-40,-40},{80,80}}
#define  ROLE__TYPE	2
#define  ROLE__SPEED	3

			/*ai1的参数定义*/
#define  AI1_NAME	"enemy"
#define  AI1_DATA	"enemy_fire/laowang.ExportJson"
#define  AI1_ATK	 50 
#define  AI1_ATKLIMIT   80
#define  AI1_HP	 10000
#define  AI1_ID	2
#define  AI1_LOCKLIMIT 200
#define	 AI1_PLAYER_NAME "火"
#define  AI1_HITRECT	{{40,-40},{80,80}}
#define  AI1_GETHITRECT  {{-40,-40},{80,80}}
#define  AI1__TYPE	2
#define  AI1__SPEED	3



using namespace cocostudio;

typedef enum
{
	TYPE_HERO = 1,
	TYPE_MONSTER = 2,
}ROLE_TYPE;

class BaseRole:public Node
{
public:
	static BaseRole * createWithProperty(propertyManager * manager);
	bool init(propertyManager * manager);

public:
	propertyManager * property;
	//保存变量
	ROLE_TYPE type;

	//创建角色动画的对象
	CC_SYNTHESIZE(Armature *, armature, Armature);

};

#endif // !__BaseRole_h__
