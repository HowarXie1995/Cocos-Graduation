#include "BaseFSM.h"

BaseFSM * BaseFSM::createFSM(BaseRole * baseRole)
{
	BaseFSM * baseFSM = new BaseFSM();
	if (baseFSM && baseFSM->init(baseRole))
	{
		baseFSM->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(baseFSM);
	}
	return baseFSM;
}

bool BaseFSM::init(BaseRole * baseRole)
{
	role = baseRole;
	return true;
}

void BaseFSM::switchMoveState(int dir)
{
	//判断当前人物状态
	if (role->state == ROLE_ATTACK)
	{
		return ;
	}
	switch (dir)
	{
	case 0:
		this->changeToDefault();
		break;
	case 1:
		this->changeToRight();
		break;
	case 3:
		this->changeToLeft();
		break;
	default:
		role->getArmature()->stopAllActions();
		break;

	}
}

void BaseFSM::changeToDefault()
{
	//判断当前的角色状态，是否为默认状态
		//如果不是默认和死亡状态和释放状态
	if (role->state != ROLE_DEFAULT && role->state != ROLE_DEAD && role->state != ROLE_FREE)
	{
		//切换为默认状态
		role->state = ROLE_DEFAULT;
		role->getArmature()->getAnimation()->play("default");
	}
}

void BaseFSM::changeToAttack()
{
	//判断当前的角色状态，是否为攻击状态
		//如果不是攻击和死亡状态
	if (role->state != ROLE_ATTACK && role->state != ROLE_DEAD)
	{
		//切换为攻击状态
		role->state = ROLE_ATTACK;
		//只循环一次
		role->getArmature()->getAnimation()->play("attack", -1, 0);
	}

}

void BaseFSM::changeToLeft()
{
	//如果角色的状态不为移动状态，并且没死
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	//人朝左  脸朝右  播放的应该是倒退动画
	if (role->face == FACE_RIGHT)
	{
		std::string movent = role->getArmature()->
			getAnimation()->getCurrentMovementID();
		char * nowMovent = const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent, "run_back") != 0)
		{
			role->getArmature()->getAnimation()->play("run_back");
		}
	}
	else
	{
		std::string movent = role->getArmature()->
			getAnimation()->getCurrentMovementID();
		char * nowMovent = const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent, "run_front") != 0)
		{
			role->getArmature()->getAnimation()->play("run_front");
		}
	}
	//重新设置角色的位置
		//朝左为-
	role->setPosition(Vec2(role->getPositionX() - role->property->getSped(), role->getPositionY()));
}

void BaseFSM::changeToRight()
{
	//如果角色的状态不为移动状态，并且没死
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	//人朝右  脸朝右  播放的应该是前进动画
	if (role->face == FACE_RIGHT)
	{
		std::string movent = role->getArmature()->
			getAnimation()->getCurrentMovementID();
		char * nowMovent = const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent, "run_front") != 0)
		{
			role->getArmature()->getAnimation()->play("run_front");
		}
	}
	else
	{
		std::string movent = role->getArmature()->
			getAnimation()->getCurrentMovementID();
		char * nowMovent = const_cast<char *>(movent.c_str());
		if (strcmp(nowMovent, "run_back") != 0)
		{
			role->getArmature()->getAnimation()->play("run_back");
		}
	}
		//朝右为+
	role->setPosition(Vec2(role->getPositionX() + role->property->getSped(), role->getPositionY()));

}

void BaseFSM::changeToDead()
{
	//判断当前的角色状态，是否为死亡状态
		//如果死亡状态
	if (role->state != ROLE_DEAD)
	{
		//切换为死亡状态
		role->state = ROLE_DEAD;
		role->getArmature()->getAnimation()->play("death", -1, 0);
	}

}

void BaseFSM::changeToEnemy()
{
}

void BaseFSM::purge()
{
	role = nullptr;
	CC_SAFE_RELEASE(this);
}
