#include "BaseRole.h"
#include "BaseFSM.h"
#include "BaseAI.h"

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
	std::cout << "Name :" << property->getArmatureName() << std::endl;
	armature = Armature::create(property->getArmatureName());
	armature->getAnimation()->play("default");		//播放待机动画
	this->addChild(armature);

	//添加回调事件
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaseRole::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return true;
}

void BaseRole::changeFace(ROLE_FACE face)
{
	//判断当前人物的朝向
		//朝左
	if (face == FACE_LEFT)
	{
		//角色动画的翻转
		armature->setScaleX(-1);
		//修改攻击矩形,翻转攻击框
		property->setHitRect(Rect(-property->getHitPoint().x - property->
		getHitRect().size.width, property->getHitRect().origin.y,property
		->getHitRect().size.width, property->getHitRect().size.height));

		this->face = face;
	}
	if (face == FACE_RIGHT)
	{
		armature->setScaleX(1);
		//翻转攻击框
		property->setHitRect(Rect(property->getHitPoint().x, property->getHitRect().origin.y,
			property->getHitRect().size.width, property->getHitRect().size.height));
		this->face = face;
	}
}

void BaseRole::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(BaseRole::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void BaseRole::onDraw(const cocos2d::Mat4 & transform, uint32_t flags)
{
	Director * director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
	/***************攻击框 的实现**************************/
	Rect rect = property->getHitRect();
	//绘制为蓝色
	Vec2 x = Vec2(rect.getMinX(), rect.getMinY());
	Vec2 y = Vec2(rect.getMaxX(), rect.getMaxY());
	DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
	DrawPrimitives::drawRect(x, y);

	/***************受击框 的实现**************************/
	rect = property->getGetHitRect();
	//绘制为绿色
	x = Vec2(rect.getMinX(), rect.getMinY());
	y = Vec2(rect.getMaxX(), rect.getMaxY());
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	DrawPrimitives::drawRect(x, y);

	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void BaseRole::animationEvent(Armature * pArmature, MovementEventType movementType, const std::string & movementIDstr)
{
	//获得movementIDstr
	const char * movementID = movementIDstr.c_str();
	if (strcmp(movementID, "attack") == 0)
	{
		//刚开始播放回调
		if (movementType == START)
		{	//碰撞检测
			//判断索敌对象是否为空 判断当前是否为死亡状态
			if (lockRole != nullptr && state != ROLE_DEAD)
			{
				//如果英雄真实的受击框与敌人真实的攻击框重合
				if (getRealRect(this, property->getHitRect()).intersectsRect
				(lockRole->getRealRect(lockRole, property->getGetHitRect())))
				{
					//证明击中了,调用飘血的方法
					int atk = property->getATK();
					//把int类型转换为const char *类型的数据
					__String * hpStr = __String::createWithFormat("%d", atk);
					//调用被锁定角色的掉血
					lockRole->fallHP(hpStr->getCString());
					//修改Hp
					lockRole->property->setHP(lockRole->property->getHP() - atk);
					//判断是否小于等于0
					if (lockRole->property->getHP() <= 0)
					{
						lockRole->getBaseAI()->stopRoleAI();
						lockRole->getBaseFSM()->changeToDead();
					}
					
				}
			}

		}
		//结束时候回调
		if (movementType == COMPLETE)
		{
			baseFSM->changeToDefault();
		}
	}
	//如果播放击倒动画
	if (strcmp(movementID, "death") == 0)
	{
		//等动画播放完后，释放
		if (movementType == COMPLETE)
		{
			//把角色状态切换到free
			armature->runAction(Sequence::create(FadeOut::create(0.5), 
					CallFunc::create([=]() {
						state = ROLE_FREE;
						}),
						NULL));

		}
	}
}

Rect BaseRole::getRealRect(BaseRole * role, Rect rect)
{
	//设置真正的矩形框起始点
	Rect realRect = Rect(rect.origin.x + role->getPositionX(),
		rect.origin.y + role->getPositionY(), rect.size.width,
		rect.size.height);

	//返回以世界坐标系，计算的矩形
	return realRect;
}

void BaseRole::fallHP(const char * hpCount)
{
	//创建对象，把hpCout传入
	FlyText * flyText = FlyText::create(hpCount);
	//开启动画
	flyText->startAnimation();
	//添加到节点上
	this->addChild(flyText);
}

void BaseRole::purge()
{
	this->getBaseFSM()->purge();
	this->getBaseAI()->purge();
	//删除自己
	removeFromParent();
}
