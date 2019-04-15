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
	//判断heroVec容器是否为空
	if (heroVec.size() != 0)
	{
		for (int i = 0; i < heroVec.size(); i++)
		{
			heroVec[i]->purge();
		}
	}
	//monster容器是否为空
	if (monsterVec.size() != 0)
	{
		for (int i = 0; i < monsterVec.size(); i++)
		{
			monsterVec[i]->purge();
		}
	}
	//容器清空
	heroVec.clear();
	heroVec.shrink_to_fit();
	monsterVec.clear();
	heroVec.shrink_to_fit();
}

BaseRole * RoleCardController::getHero()
{
	//遍历容器，找到与角色相同的ID那个BaseRole
	for (int i = 0; i < heroVec.size(); i++)
	{
		if (heroVec[i]->property->getID() == this->getHeroID())
		{
			//找到了，返回
			return heroVec[i];
		}
	}
	//没找到返回空
	return nullptr;
}
