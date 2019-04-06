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
