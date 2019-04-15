#include "ControlLayer.h"
#include "BaseAI.h"
#include "cocos-ext.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "DataManager.h"

USING_NS_CC;
USING_NS_CC_MATH;


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
	Level = DataManager::getInstance()->getLevelIndex();
	//�����ǰiС�ڵ�ǰ�ؿ�������ɫ��Ϣ������
	for (unsigned int i = 0; i < DataManager::getInstance()->getLevelDataArrayByIndex(
		DataManager::getInstance()->getLevelIndex()).size(); ++i)
	{	/**********ִ�д�����ɫ**************/
		//��ȡ.json�ļ�
		std::string roleDataStr = FileUtils::getInstance()->getStringFromFile(
		DataManager::getInstance()->_levelDataArray[i]);
		rapidjson::Document roleMap;
		roleMap.Parse<0>(roleDataStr.c_str());

		//�Խ�ɫ���Գ�ʼ��
		propertyManager * pManager = propertyManager::create();
		pManager->setArmatureName(roleMap["ArmatureName"].GetString());
		pManager->setDataName(roleMap["DataName"].GetString());
		pManager->setATK(roleMap["ATK"].GetInt());
		pManager->setHP(roleMap["HP"].GetInt());
		pManager->setID(roleMap["ID"].GetInt());
		pManager->setLockLimit(roleMap["LockLimit"].GetInt());
		pManager->setATKLimit(roleMap["ATKLimit"].GetInt());
		pManager->setPlayerName(roleMap["PlayerName"].GetString());
		pManager->setSped(roleMap["Speed"].GetInt());
		pManager->setHitRect(RectFromString(roleMap["HitRect"].GetString()));
		pManager->setHitPoint(pManager->getHitRect().origin);
		pManager->setGetHitRect(RectFromString(roleMap["GetHitRect"].GetString()));
		pManager->setGetHitPoint(pManager->getGetHitRect().origin);
		pManager->retain();	//��ֹ�������ͷ�

		//����һ����ɫ����
		BaseRole *role = BaseRole::createWithProperty(pManager);
		role->setPosition(Vec2(200, 200));
		role->type = static_cast<ROLE_TYPE>(roleMap["Type"].GetInt());
		role->face = FACE_RIGHT;
		this->addChild(role, 1, 1);
		//�ж��ǹ��ﻹ��Ӣ��
		if(role->type == TYPE_MONSTER)
		{ 
			RoleCardController::getInstance()->monsterVec.push_back(role);
			//���ù���λ��
					//���������0.8 �ߵ�0.4
			role->setPosition(Vec2(Director::getInstance()->getVisibleSize().width *0.8,
				Director::getInstance()->getVisibleSize().height * 0.3));
		}
		else if (role->type == TYPE_HERO)
		{
			//����Ӣ�۵�λ��
					//���������0.2 �ߵ�0.4
			RoleCardController::getInstance()->heroVec.push_back(role);
			role->setPosition(Vec2(Director::getInstance()->getVisibleSize().width *0.2,
				Director::getInstance()->getVisibleSize().height * 0.3));
		}
		//����ɫ����ai
		BaseAI * ai = BaseAI::createAI(role);
		ai->retain();
		role->setBaseAI(ai);
		//ִ��ai
		ai->startRoleAI();
		//����ɫ����״̬
		BaseFSM * baseFSM = BaseFSM::createFSM(role);
		baseFSM->retain();
		role->setBaseFSM(baseFSM);
	}


	//��MapLayer��ӵ�ControlLayer����
	MapLayer * mapLayer = MapLayer::create();
	//ִ�а󶨱���ͼ�ķ���
	mapLayer->setBackGronud("background.png");
	this->addChild(mapLayer);

	//д��ID
	RoleCardController::getInstance()->setHeroID(1);

	//�Ѳ�������ӵ�controlLayer����
	OperateLayer * operateLayer = OperateLayer::create();
	this->addChild(operateLayer);

	//����һ��rocker�Ķ���
	rocker = HRocker::createHRocker("center.png", "direction.png",
		Vec2(200, 200));
	rocker->startRoker(true);
	this->addChild(rocker, 1);
	Director::getInstance()->getScheduler()->
		schedule(schedule_selector(ControlLayer::update), this, (float)1 / 60, false);
	
	return true;
}

void ControlLayer::update(float dt)
{
	if (Level != DataManager::getInstance()->getLevelIndex())
	{
		return;
	}
	//�ӽ�ɫ�����������ȡ��ɫ
	if (RoleCardController::getInstance()->getHero() != nullptr)
	{
		//�û�ȡ����Ӣ�۶�����ҡ�˰�
		RoleCardController::getInstance()->getHero()->getBaseFSM()
			->switchMoveState(rocker->rockerDirection);
	}
	//����һ��������������monster������
	std::vector<BaseRole *>::iterator itr = RoleCardController::getInstance()->monsterVec.begin();
	while (itr != RoleCardController::getInstance()->monsterVec.end())
	{
		//����ROLE_FREEʱ�����ͷ�
		if ((*itr)->state == ROLE_FREE)
		{
			(*itr)->purge();
			RoleCardController::getInstance()->monsterVec.erase(itr);
			break;
		}
		++itr;
	}
	if (RoleCardController::getInstance()->monsterVec.size() == 0)
	{
		//����������һ�ؽ���
		if (DataManager::getInstance()->getLevelIndex() == 2)
		{		
			Get_Screen_winSize;
			Label * label = Label::createWithTTF("����ʤ��",	//��ǩ����
			"fonts/white.ttf",			//����
			70);						//�����С
			label->setPosition(Vec2(winSize.width  / 2, winSize.height * 5 / 6));
			label->setColor(Color3B::BLACK);
			this->addChild(label,1);
			return;
		}

		//�����ͷŶ���ķ���
		this->purge();
		//��ȡ��һ�ص�����
						Get_Screen_winSize;
			Label * label = Label::createWithTTF("����˵��ˣ�������һ��",	//��ǩ����
			"fonts/white.ttf",			//����
			70);						//�����С
			label->setPosition(Vec2(winSize.width  / 2, winSize.height * 5 / 6));
			label->setColor(Color3B::BLACK);
			this->addChild(label,1);
	//��ǰһ�صĻ���+1
		scheduleOnce(CC_SCHEDULE_SELECTOR(ControlLayer::onScheduleOnce),	//����ص�����	
					2.0);		//����

	}

	//����һ��������������hero������
	itr = RoleCardController::getInstance()->heroVec.begin();
	while (itr != RoleCardController::getInstance()->heroVec.end())
	{
		//����ROLE_FREEʱ�����ͷ�
		if ((*itr)->state == ROLE_FREE)
		{
			(*itr)->purge();
			RoleCardController::getInstance()->heroVec.erase(itr);
			break;
		}
		++itr;
	}
	if (RoleCardController::getInstance()->heroVec.size() == 0)
	{
		log("fail");
	}


}

void ControlLayer::purge()
{

	//ֹͣ��ʱ��
	Director::getInstance()->getScheduler()->unschedule(
		schedule_selector(ControlLayer::update), this);
	//����RoleCar������ͷŷ���
	RoleCardController::getInstance()->purge();
	//this->removeFromParent();
}

void ControlLayer::onScheduleOnce(float dt)
{
		DataManager::getInstance()->setLevelIndex(DataManager::getInstance()->getInstance()->getLevelIndex() + 1);
		Sleep(2000);
		tsm->goGameScene();
}
