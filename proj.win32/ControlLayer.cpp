#include "ControlLayer.h"
#include "BaseAI.h"
#include "cocos-ext.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "DataManager.h"

USING_NS_CC;
USING_NS_CC_MATH;


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
	Level = DataManager::getInstance()->getLevelIndex();
	//如果当前i小于当前关卡包含角色信息的数量
	for (unsigned int i = 0; i < DataManager::getInstance()->getLevelDataArrayByIndex(
		DataManager::getInstance()->getLevelIndex()).size(); ++i)
	{	/**********执行创建角色**************/
		//读取.json文件
		std::string roleDataStr = FileUtils::getInstance()->getStringFromFile(
		DataManager::getInstance()->_levelDataArray[i]);
		rapidjson::Document roleMap;
		roleMap.Parse<0>(roleDataStr.c_str());

		//对角色属性初始化
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
		pManager->retain();	//防止创建被释放

		//创建一个角色的类
		BaseRole *role = BaseRole::createWithProperty(pManager);
		role->setPosition(Vec2(200, 200));
		role->type = static_cast<ROLE_TYPE>(roleMap["Type"].GetInt());
		role->face = FACE_RIGHT;
		this->addChild(role, 1, 1);
		//判断是怪物还是英雄
		if(role->type == TYPE_MONSTER)
		{ 
			RoleCardController::getInstance()->monsterVec.push_back(role);
			//设置怪物位置
					//可视区宽的0.8 高的0.4
			role->setPosition(Vec2(Director::getInstance()->getVisibleSize().width *0.8,
				Director::getInstance()->getVisibleSize().height * 0.3));
		}
		else if (role->type == TYPE_HERO)
		{
			//设置英雄的位置
					//可视区宽的0.2 高的0.4
			RoleCardController::getInstance()->heroVec.push_back(role);
			role->setPosition(Vec2(Director::getInstance()->getVisibleSize().width *0.2,
				Director::getInstance()->getVisibleSize().height * 0.3));
		}
		//给角色创建ai
		BaseAI * ai = BaseAI::createAI(role);
		ai->retain();
		role->setBaseAI(ai);
		//执行ai
		ai->startRoleAI();
		//给角色创建状态
		BaseFSM * baseFSM = BaseFSM::createFSM(role);
		baseFSM->retain();
		role->setBaseFSM(baseFSM);
	}


	//把MapLayer添加到ControlLayer上面
	MapLayer * mapLayer = MapLayer::create();
	//执行绑定背景图的方法
	mapLayer->setBackGronud("background.png");
	this->addChild(mapLayer);

	//写入ID
	RoleCardController::getInstance()->setHeroID(1);

	//把操作层添加到controlLayer上面
	OperateLayer * operateLayer = OperateLayer::create();
	this->addChild(operateLayer);

	//创建一个rocker的对象
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
	//从角色控制类里面获取角色
	if (RoleCardController::getInstance()->getHero() != nullptr)
	{
		//让获取到的英雄动作与摇杆绑定
		RoleCardController::getInstance()->getHero()->getBaseFSM()
			->switchMoveState(rocker->rockerDirection);
	}
	//创建一个迭代器，遍历monster的容器
	std::vector<BaseRole *>::iterator itr = RoleCardController::getInstance()->monsterVec.begin();
	while (itr != RoleCardController::getInstance()->monsterVec.end())
	{
		//等于ROLE_FREE时调用释放
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
		//如果到了最后一关结束
		if (DataManager::getInstance()->getLevelIndex() == 2)
		{		
			Get_Screen_winSize;
			Label * label = Label::createWithTTF("最后的胜利",	//标签名字
			"fonts/white.ttf",			//字体
			70);						//字体大小
			label->setPosition(Vec2(winSize.width  / 2, winSize.height * 5 / 6));
			label->setColor(Color3B::BLACK);
			this->addChild(label,1);
			return;
		}

		//调用释放对象的方法
		this->purge();
		//读取下一关的数据
						Get_Screen_winSize;
			Label * label = Label::createWithTTF("打败了敌人，进入下一关",	//标签名字
			"fonts/white.ttf",			//字体
			70);						//字体大小
			label->setPosition(Vec2(winSize.width  / 2, winSize.height * 5 / 6));
			label->setColor(Color3B::BLACK);
			this->addChild(label,1);
	//在前一关的基础+1
		scheduleOnce(CC_SCHEDULE_SELECTOR(ControlLayer::onScheduleOnce),	//加入回调函数	
					2.0);		//秒数

	}

	//创建一个迭代器，遍历hero的容器
	itr = RoleCardController::getInstance()->heroVec.begin();
	while (itr != RoleCardController::getInstance()->heroVec.end())
	{
		//等于ROLE_FREE时调用释放
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

	//停止定时器
	Director::getInstance()->getScheduler()->unschedule(
		schedule_selector(ControlLayer::update), this);
	//调用RoleCar里面的释放方法
	RoleCardController::getInstance()->purge();
	//this->removeFromParent();
}

void ControlLayer::onScheduleOnce(float dt)
{
		DataManager::getInstance()->setLevelIndex(DataManager::getInstance()->getInstance()->getLevelIndex() + 1);
		Sleep(2000);
		tsm->goGameScene();
}
