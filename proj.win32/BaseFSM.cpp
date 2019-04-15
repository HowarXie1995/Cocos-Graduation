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
	//�жϵ�ǰ����״̬
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
	//�жϵ�ǰ�Ľ�ɫ״̬���Ƿ�ΪĬ��״̬
		//�������Ĭ�Ϻ�����״̬���ͷ�״̬
	if (role->state != ROLE_DEFAULT && role->state != ROLE_DEAD && role->state != ROLE_FREE)
	{
		//�л�ΪĬ��״̬
		role->state = ROLE_DEFAULT;
		role->getArmature()->getAnimation()->play("default");
	}
}

void BaseFSM::changeToAttack()
{
	//�жϵ�ǰ�Ľ�ɫ״̬���Ƿ�Ϊ����״̬
		//������ǹ���������״̬
	if (role->state != ROLE_ATTACK && role->state != ROLE_DEAD)
	{
		//�л�Ϊ����״̬
		role->state = ROLE_ATTACK;
		//ֻѭ��һ��
		role->getArmature()->getAnimation()->play("attack", -1, 0);
	}

}

void BaseFSM::changeToLeft()
{
	//�����ɫ��״̬��Ϊ�ƶ�״̬������û��
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	//�˳���  ������  ���ŵ�Ӧ���ǵ��˶���
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
	//�������ý�ɫ��λ��
		//����Ϊ-
	role->setPosition(Vec2(role->getPositionX() - role->property->getSped(), role->getPositionY()));
}

void BaseFSM::changeToRight()
{
	//�����ɫ��״̬��Ϊ�ƶ�״̬������û��
	if (role->state != ROLE_MOVE && role->state != ROLE_DEAD)
	{
		role->state = ROLE_MOVE;
	}
	//�˳���  ������  ���ŵ�Ӧ����ǰ������
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
		//����Ϊ+
	role->setPosition(Vec2(role->getPositionX() + role->property->getSped(), role->getPositionY()));

}

void BaseFSM::changeToDead()
{
	//�жϵ�ǰ�Ľ�ɫ״̬���Ƿ�Ϊ����״̬
		//�������״̬
	if (role->state != ROLE_DEAD)
	{
		//�л�Ϊ����״̬
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
