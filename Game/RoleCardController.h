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
	
public:
	//���� ��׼������vector
	std::vector<BaseRole *>heroVec;		//Ӣ������
	std::vector<BaseRole *>monsterVec;	//��������
};

#endif // __RoleCardController_h__
