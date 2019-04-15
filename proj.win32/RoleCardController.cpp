#include "RoleCardController.h"

static RoleCardController * roleCardController = nullptr;

RoleCardController * RoleCardController::getInstance()
{
	if (roleCardController == nullptr)
	{
		roleCardController = new(std::nothrow)RoleCardController();
		roleCardController->init();
	}
	return roleCardController;
}

bool RoleCardController::init()
{
	return true;
}

void RoleCardController::purge()
{
	//�ж�heroVec�����Ƿ�Ϊ��
	if (heroVec.size() != 0)
	{
		for (int i = 0; i < heroVec.size(); i++)
		{
			heroVec[i]->purge();
		}
	}
	//monster�����Ƿ�Ϊ��
	if (monsterVec.size() != 0)
	{
		for (int i = 0; i < monsterVec.size(); i++)
		{
			monsterVec[i]->purge();
		}
	}
	//�������
	heroVec.clear();
	heroVec.shrink_to_fit();
	monsterVec.clear();
	heroVec.shrink_to_fit();
}

BaseRole * RoleCardController::getHero()
{
	//�����������ҵ����ɫ��ͬ��ID�Ǹ�BaseRole
	for (int i = 0; i < heroVec.size(); i++)
	{
		if (heroVec[i]->property->getID() == this->getHeroID())
		{
			//�ҵ��ˣ�����
			return heroVec[i];
		}
	}
	//û�ҵ����ؿ�
	return nullptr;
}
