#include "ControlLayer.h"
#include "MapLayer.h"
#include "OperateLayer.h"
#include "HRocker.h"
#include "BaseRole.h"


//把中文转成utf-8格式输出
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32



bool ControlLayer::init()
{	
	if (!Layer::init())
	{
		return false;
	}

	//读取plist文件
	auto roleMap = FileUtils::getInstance()->getValueMapFromFile("hero.plist");
	//对角色属性初始化
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
	pManager->retain();	//防止创建被释放

	//创建一个角色的类
	auto hero = BaseRole::createWithProperty(pManager);
	hero->setPosition(Vec2(200, 200));
	hero->type = static_cast<ROLE_TYPE>(ROLE__TYPE);
	this->addChild(hero,1, 1);

	//读取plist文件
	auto monsterMap = FileUtils::getInstance()->getValueMapFromFile("test.plist");
	//对ai角色属性初始化
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
	mManager->retain();	//防止创建被释放

	//创建一个角色的类
	/*
	auto moster = BaseRole::createWithProperty(mManager);
	moster->setPosition(Vec2(800, 200));
	moster->type = static_cast<ROLE_TYPE>(AI1__TYPE);
	this->addChild(moster, 2, 1);
	*/

	//把MapLayer添加到ControlLayer上面
	MapLayer * mapLayer = MapLayer::create();
	//执行绑定背景图的方法
	mapLayer->setBackGronud("background.png");
	this->addChild(mapLayer);

	//把操作层添加到controlLayer上面
	OperateLayer * operateLayer = OperateLayer::create();
	this->addChild(operateLayer);

	//创建一个rocker的对象
	HRocker * rocker = HRocker::createHRocker("center.png", "direction.png",
		Vec2(200, 200));
	rocker->startRoker(true);
	this->addChild(rocker, 1);
	
	return true;
}
