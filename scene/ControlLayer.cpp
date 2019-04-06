#include "ControlLayer.h"
#include "MapLayer.h"
#include "OperateLayer.h"
#include "HRocker.h"
#include "BaseRole.h"


//������ת��utf-8��ʽ���
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32



bool ControlLayer::init()
{	
	if (!Layer::init())
	{
		return false;
	}

	//��ȡplist�ļ�
	auto roleMap = FileUtils::getInstance()->getValueMapFromFile("hero.plist");
	//�Խ�ɫ���Գ�ʼ��
	propertyManager * pManager = propertyManager::create();
	pManager->setArmatureName(ROLE_NAME/*roleMap["ArmatureName"].asString()*/);
	pManager->setDataName(ROLE_DATA/*roleMap["DataName"].asString()*/);
	pManager->setATK(ROLE_ATK/*roleMap["ATK"].asInt()*/);
	pManager->setHP(ROLE_HP/*roleMap["HP"].asInt()*/);
	pManager->setID(ROLE_ID/*roleMap["ID"].asInt()*/);
	pManager->setLockLimit(ROLE_LOCKLIMIT/*roleMap["LockLimit"].asInt()*/);
	pManager->setATKLimit(ROLE_ATKLIMIT/*roleMap["ATKLimit"].asInt()*/);
	pManager->setPlayerName(ROLE_PLAYER_NAME/*roleMap["PlayerName"].asString()*/);
	pManager->setHitRect(ROLE_HITRECT/*RectFromString(roleMap["HitRect"].asString())*/);
	pManager->setHitPoint(pManager->getHitRect().origin);
	pManager->setGetHitRect(ROLE_GETHITRECT/*RectFromString(roleMap["GetHitRect"].asString())*/);
	pManager->setGetHitPoint(pManager->getGetHitRect().origin);
	pManager->retain();	//��ֹ�������ͷ�

	//����һ����ɫ����
	auto hero = BaseRole::createWithProperty(pManager);
	hero->setPosition(Vec2(200, 200));
	hero->type = static_cast<ROLE_TYPE>(ROLE__TYPE);
	this->addChild(hero,1, 1);

	//��ȡplist�ļ�
	auto monsterMap = FileUtils::getInstance()->getValueMapFromFile("test.plist");
	//��ai��ɫ���Գ�ʼ��
	propertyManager * mManager = propertyManager::create();
	mManager->setArmatureName(AI1_NAME/*roleMap["ArmatureName"].asString()*/);
	mManager->setDataName(AI1_DATA/*roleMap["DataName"].asString()*/);
	mManager->setATK(AI1_ATK/*roleMap["ATK"].asInt()*/);
	mManager->setHP(AI1_HP/*roleMap["HP"].asInt()*/);
	mManager->setID(AI1_ID/*roleMap["ID"].asInt()*/);
	mManager->setLockLimit(AI1_LOCKLIMIT/*roleMap["LockLimit"].asInt()*/);
	mManager->setATKLimit(AI1_ATKLIMIT/*roleMap["ATKLimit"].asInt()*/);
	mManager->setPlayerName(AI1_PLAYER_NAME/*roleMap["PlayerName"].asString()*/);
	mManager->setHitRect(AI1_HITRECT/*RectFromString(roleMap["HitRect"].asString())*/);
	mManager->setHitPoint(mManager->getHitRect().origin);
	mManager->setGetHitRect(AI1_GETHITRECT/*RectFromString(roleMap["GetHitRect"].asString())*/);
	mManager->setGetHitPoint(mManager->getGetHitRect().origin);
	mManager->retain();	//��ֹ�������ͷ�

	//����һ����ɫ����
	/*
	auto moster = BaseRole::createWithProperty(mManager);
	moster->setPosition(Vec2(800, 200));
	moster->type = static_cast<ROLE_TYPE>(AI1__TYPE);
	this->addChild(moster, 2, 1);
	*/

	//��MapLayer��ӵ�ControlLayer����
	MapLayer * mapLayer = MapLayer::create();
	//ִ�а󶨱���ͼ�ķ���
	mapLayer->setBackGronud("background.png");
	this->addChild(mapLayer);

	//�Ѳ�������ӵ�controlLayer����
	OperateLayer * operateLayer = OperateLayer::create();
	this->addChild(operateLayer);

	//����һ��rocker�Ķ���
	HRocker * rocker = HRocker::createHRocker("center.png", "direction.png",
		Vec2(200, 200));
	rocker->startRoker(true);
	this->addChild(rocker, 1);
	
	return true;
}
