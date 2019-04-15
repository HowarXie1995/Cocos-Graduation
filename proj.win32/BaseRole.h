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

typedef enum      //�����ɫ��״̬
{
	ROLE_DEFAULT = 1,
	ROLE_ATTACK,
	ROLE_MOVE,
	ROLE_DEAD,
	ROLE_FREE,		//�ͷ�״̬
}ROLE_STATE;

typedef enum    //�����ɫ������
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
	//�ı�������ķ���
	void changeFace(ROLE_FACE face);
	virtual void draw(cocos2d::Renderer * renderer, \
		const cocos2d::Mat4&transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCommand;
	//�ص�����:��ΪĬ��״̬
	void animationEvent(Armature * pArmature, MovementEventType movementType, 
			const std::string & movementIDstr);
	//�����ײ���ľ�����
	Rect getRealRect(BaseRole * role, Rect rect);
	void fallHP(const char *hpCount);
	//�ͷŵķ���
	void purge();
public:
	BaseRole * lockRole;		//���ж���
	propertyManager * property;
	//�������
	ROLE_TYPE type;
	ROLE_STATE state;
	ROLE_FACE face;

	//������ɫ�����Ķ���
	CC_SYNTHESIZE(Armature *, armature, Armature);
	CC_SYNTHESIZE(BaseFSM *, baseFSM, BaseFSM);
	CC_SYNTHESIZE(BaseAI *, baseAI, BaseAI);

};

#endif // !__BaseRole_h__
