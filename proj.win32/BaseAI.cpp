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
	//�������˵�����
	std::vector<BaseRole *>roleVec;
		//�����Ӣ��
	if (baseRole->type == TYPE_HERO)
	{
		//���������ڹ���
		roleVec = RoleCardController::getInstance()->monsterVec;
	}
		//����ǹ���
	else if (baseRole->type == TYPE_MONSTER)
	{
		//����������Ӣ��
		roleVec = RoleCardController::getInstance()->heroVec;

	}

	int roleID = 0;		//���
	if (roleVec.size() != 0 )
	{
		//�þ��������Ļ���
		float distance;		//�������
		//��������
		for (int i = 0; i < roleVec.size(); i++)
		{
			distance =  Director::getInstance()->getVisibleSize().width;
			//��þ���
			float newDis = abs(baseRole->getPosition().distance(roleVec[i]->getPosition()));
			//����¾���С��ԭ��Ĭ�ϵľ���
			if (newDis < distance)
			{
				roleID = i;
				distance = newDis;
			}
		}
		//������˵�x���� ���� ��ɫ��x����
		float a = roleVec[roleID]->getPositionX();
		float b = baseRole->getPositionX();
		if (roleVec[roleID]->getPositionX() > baseRole->getPositionX())
		{
			baseRole->changeFace(FACE_RIGHT);		//����
		}
		else
		{
			baseRole->changeFace(FACE_LEFT);		//����
		}
	}
	else//���û�е���
	{
		baseRole->lockRole = nullptr;
		return;
	}
	//�����������Ϊ���ж���
	baseRole->lockRole = roleVec[roleID];
	//�жϵ�ǰ��ɫ�Ƿ�Ϊmonster����
		//���Ϊmonster����
	if (baseRole->type == TYPE_MONSTER)
	{
		Vec2 enemyPos = roleVec[roleID]->getPosition();
		//С����������
		if (baseRole->getPosition().distance(enemyPos) < baseRole->property->getLockLimit())
		{
			//�ж��Ƿ�С�ڹ�����
			if (baseRole->getPosition().distance(enemyPos) < baseRole->
				property->getATKLimit())
			{
				//��Ϊ����״̬�����Ź�������
				baseRole->getBaseFSM()->changeToAttack();
			}
			else//����ڹ�������������֮��
			{	
				//�����ɫ�����Ҳ��ǹ���״̬
				if (baseRole->face == FACE_LEFT && baseRole->state
					!= ROLE_ATTACK)
				{
					//��ɫ�����ƶ�
					baseRole->getBaseFSM()->changeToLeft();
				}
				//�����ɫ���ң��Ҳ��ǹ���״̬
				else if (baseRole->face == FACE_RIGHT
					&& baseRole->state != ROLE_ATTACK)
				{
					//��ɫ�����ƶ�
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
