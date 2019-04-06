#ifndef __RoleCardController_h__
#define __RoleCardController_h__

#include <iostream>
#include <cocos2d.h>
#include "BaseRole.h"
USING_NS_CC;

//µ¥ÀýÄ£Ê½
class RoleCardController:public Ref
{
public:
	static RoleCardController * getInstance();
	bool init();
	
public:
	//ÈÝÆ÷ ±ê×¼¿âÈÝÆ÷vector
	std::vector<BaseRole *>heroVec;		//Ó¢ÐÛÈÝÆ÷
	std::vector<BaseRole *>monsterVec;	//µÐÈËÈÝÆ÷
};

#endif // __RoleCardController_h__
