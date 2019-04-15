#include "OperateLayer.h"
#include "RoleCardController.h"
#include "HRocker.h"
#include "BaseFSM.h"

bool OperateLayer::init()
{
	Get_Screen_winSize;
	Button * button = Button::create();
	button->loadTextures("attck_bt.png", "");
	button->setPosition(Vec2(winSize.width * 5 / 6, winSize.height  / 6));
	button->addTouchEventListener(CC_CALLBACK_2(OperateLayer::touchCallBack, this));
	this->addChild(button);


	return true;
}

void OperateLayer::touchCallBack(Ref * sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
	{
		auto button = static_cast<Button*>(sender);
		//通过角色控制器取到英雄对象
		RoleCardController::getInstance()->getHero()->getBaseFSM()->changeToAttack();

	}
}
