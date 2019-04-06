#include "BaseRole.h"

BaseRole * BaseRole::createWithProperty(propertyManager * manager)
{
	BaseRole * baseRole = new BaseRole();
	if (baseRole && baseRole->init(manager))
	{
		baseRole->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(baseRole);
		return nullptr;
	}
	return baseRole;
}

bool BaseRole::init(propertyManager * manager)
{
	property = manager;
	ArmatureDataManager::getInstance()->addArmatureFileInfo(
		property->getDataName());
	armature = Armature::create(property->getArmatureName());
	armature->getAnimation()->play("default");		//²¥·Å´ı»ú¶¯»­
	this->addChild(armature);
	return true;
}
