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
	//���ٴ���һ����Ա������������һ��set������get����
	CC_SYNTHESIZE(int, ID, ID);		//��ɫID
	CC_SYNTHESIZE(int, HP, HP);		//��ɫѪ��
	CC_SYNTHESIZE(int, ATK, ATK);	//��ɫ������
	CC_SYNTHESIZE(unsigned int, LockLimit, LockLimit);	//������
	CC_SYNTHESIZE(unsigned int, ATKLimit, ATKLimit);	//������

	CC_SYNTHESIZE(std::string, ArmatureName, ArmatureName);	//������Դ·���ı���
	CC_SYNTHESIZE(std::string, DataName, DataName);			//�������ֵı���
	CC_SYNTHESIZE(std::string, PlayerName, PlayerName);		//��ɫ���ֵı���
	
	CC_SYNTHESIZE(Rect, HitRect, HitRect);			//������
	CC_SYNTHESIZE(Point, HitPoint, HitPoint);		//��������ʼ������

	CC_SYNTHESIZE(Rect, GetHitRect, GetHitRect);			//������
	CC_SYNTHESIZE(Point, GetHitPoint, GetHitPoint);		//��������ʼ������

};

#endif // !__propertyManager_h__
