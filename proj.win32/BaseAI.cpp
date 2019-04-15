#include "BaseAI.h"
#include "RoleCardController.h"
#include "BaseFSM.h"

BaseAI * BaseAI::createAI(BaseRole * role)
{
	BaseAI * ai = new BaseAI();
	if (ai && ai->init(role))
	{
		ai->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ai);
	}
	return ai;
}

bool BaseAI::init(BaseRole * role)
{
	baseRole = role;
	return true;
}

void BaseAI::startRoleAI()
{
	Director::getInstance()->getScheduler()->
		schedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc), this,
		(float)1 / 60, false);
}

void BaseAI::stopRoleAI()
{
	Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(BaseAI::updateFunc), this);
}

void BaseAI::updateFunc(float dt)
{
	//创建敌人的容器
	std::vector<BaseRole *>roleVec;
		//如果是英雄
	if (baseRole->type == TYPE_HERO)
	{
		//让容器等于怪物
		roleVec = RoleCardController::getInstance()->monsterVec;
	}
		//如果是怪物
	else if (baseRole->type == TYPE_MONSTER)
	{
		//让容器等于英雄
		roleVec = RoleCardController::getInstance()->heroVec;

	}

	int roleID = 0;		//编号
	if (roleVec.size() != 0 )
	{
		//让距离等于屏幕宽度
		float distance;		//距离变量
		//遍历容器
		for (int i = 0; i < roleVec.size(); i++)
		{
			distance =  Director::getInstance()->getVisibleSize().width;
			//获得距离
			float newDis = abs(baseRole->getPosition().distance(roleVec[i]->getPosition()));
			//如果新距离小于原来默认的距离
			if (newDis < distance)
			{
				roleID = i;
				distance = newDis;
			}
		}
		//如果敌人的x坐标 大于 角色的x坐标
		float a = roleVec[roleID]->getPositionX();
		float b = baseRole->getPositionX();
		if (roleVec[roleID]->getPositionX() > baseRole->getPositionX())
		{
			baseRole->changeFace(FACE_RIGHT);		//朝右
		}
		else
		{
			baseRole->changeFace(FACE_LEFT);		//朝左
		}
	}
	else//如果没有敌人
	{
		baseRole->lockRole = nullptr;
		return;
	}
	//把最近的设置为索敌对象
	baseRole->lockRole = roleVec[roleID];
	//判断当前角色是否为monster类型
		//如果为monster类型
	if (baseRole->type == TYPE_MONSTER)
	{
		Vec2 enemyPos = roleVec[roleID]->getPosition();
		//小于索敌区域
		if (baseRole->getPosition().distance(enemyPos) < baseRole->property->getLockLimit())
		{
			//判断是否小于攻击区
			if (baseRole->getPosition().distance(enemyPos) < baseRole->
				property->getATKLimit())
			{
				//变为攻击状态，播放攻击动画
				baseRole->getBaseFSM()->changeToAttack();
			}
			else//如果在攻击区和索敌区之间
			{	
				//如果角色朝左，且不是攻击状态
				if (baseRole->face == FACE_LEFT && baseRole->state
					!= ROLE_ATTACK)
				{
					//角色向左移动
					baseRole->getBaseFSM()->changeToLeft();
				}
				//如果角色朝右，且不是攻击状态
				else if (baseRole->face == FACE_RIGHT
					&& baseRole->state != ROLE_ATTACK)
				{
					//角色向右移动
					baseRole->getBaseFSM()->changeToRight();
				}
			}
		}
		else
		{
			baseRole->getBaseFSM()->changeToDefault();
		}
		
	}
}

void BaseAI::purge()
{
	stopRoleAI();
	baseRole = nullptr;
	CC_SAFE_RELEASE(this);
}
