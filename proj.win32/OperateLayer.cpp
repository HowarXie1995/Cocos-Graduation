#include "OperateLayer.h"
#include "RoleCardController.h"
#include "HRocker.h"
#include "BaseFSM.h"

bool OperateLayer::init()
{
	Get_Screen_winSize;
	Button * bt_attack = Button::create();
	bt_attack->loadTextures("attck_bt.png", "");
	bt_attack->setPosition(Vec2(winSize.width * 6 / 7, winSize.height * 2 / 7));
	bt_attack->setTag(ATTACK);
	bt_attack->addTouchEventListener(CC_CALLBACK_2(OperateLayer::touchCallBack, this));
	this->addChild(bt_attack, 0);

	Button * bt_close = Button::create();
	bt_close->loadTextures("CloseSelected.png", "");
	bt_close->setPosition(Vec2(winSize.width * 14 / 15, winSize.height * 14 / 15));
	bt_close->setTag(CLOSE);
	bt_close->addTouchEventListener(CC_CALLBACK_2(OperateLayer::touchCallBack, this));
	this->addChild(bt_close);

	Button * bt_puase = Button::create();
	bt_puase->loadTextures("pause.png", "");
	bt_puase->setPosition(Vec2(winSize.width * 13 / 15, winSize.height * 14 / 15));
	bt_puase->setTag(PUASE);
	bt_puase->addTouchEventListener(CC_CALLBACK_2(OperateLayer::touchCallBack, this));
	this->addChild(bt_puase);

	return true;
}

void OperateLayer::touchCallBack(Ref * sender, Widget::TouchEventType controlEvent)
{
	if (controlEvent == Widget::TouchEventType::ENDED)
	{
		auto button = static_cast<Button*>(sender);
		switch (button->getTag())
		{
		case PUASE:	//暂停
		{
			Director::getInstance()->pause();
			button->setTag(REBACK);
		}break;
		case ATTACK://攻击
		{
			RoleCardController::getInstance()->getHero()->getBaseFSM()->changeToAttack();
		}break;
		case CLOSE: //退出
		{
			Director::getInstance()->end();
		}break;
		case REBACK://返回
		{
			Director::getInstance()->resume();
			button->setTag(PUASE);
		}
		}
		//通过角色控制器取到英雄对象

	}
}
