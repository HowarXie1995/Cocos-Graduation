#ifndef __RoleCardController_h__
#define __RoleCardController_h__

#include <iostream>
#include <cocos2d.h>
#include "BaseRole.h"
USING_NS_CC;

//����ģʽ
class RoleCardController:public Ref
{
public:
	static RoleCardController * getInstance();
	bool init();
	void purge();
	
public:
	//���� ��׼������vector
	std::vector<BaseRole *>heroVec;		//Ӣ������
	std::vector<BaseRole *>monsterVec;	//��������

	//�ɻ�ȡ����ɫID
	BaseRole * getHero();	
public:
	//����������ҿ��Ƶ�id
	CC_SYNTHESIZE(int, HeroID, HeroID);
};

#endif // __RoleCardController_h__
