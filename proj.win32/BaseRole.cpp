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
	armature->getAnimation()->play("default");		//���Ŵ�������
	this->addChild(armature);

	//��ӻص��¼�
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(BaseRole::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return true;
}

void BaseRole::changeFace(ROLE_FACE face)
{
	//�жϵ�ǰ����ĳ���
		//����
	if (face == FACE_LEFT)
	{
		//��ɫ�����ķ�ת
		armature->setScaleX(-1);
		//�޸Ĺ�������,��ת������
		property->setHitRect(Rect(-property->getHitPoint().x - property->
		getHitRect().size.width, property->getHitRect().origin.y,property
		->getHitRect().size.width, property->getHitRect().size.height));

		this->face = face;
	}
	if (face == FACE_RIGHT)
	{
		armature->setScaleX(1);
		//��ת������
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
	/***************������ ��ʵ��**************************/
	Rect rect = property->getHitRect();
	//����Ϊ��ɫ
	Vec2 x = Vec2(rect.getMinX(), rect.getMinY());
	Vec2 y = Vec2(rect.getMaxX(), rect.getMaxY());
	DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
	DrawPrimitives::drawRect(x, y);

	/***************�ܻ��� ��ʵ��**************************/
	rect = property->getGetHitRect();
	//����Ϊ��ɫ
	x = Vec2(rect.getMinX(), rect.getMinY());
	y = Vec2(rect.getMaxX(), rect.getMaxY());
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	DrawPrimitives::drawRect(x, y);

	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void BaseRole::animationEvent(Armature * pArmature, MovementEventType movementType, const std::string & movementIDstr)
{
	//���movementIDstr
	const char * movementID = movementIDstr.c_str();
	if (strcmp(movementID, "attack") == 0)
	{
		//�տ�ʼ���Żص�
		if (movementType == START)
		{	//��ײ���
			//�ж����ж����Ƿ�Ϊ�� �жϵ�ǰ�Ƿ�Ϊ����״̬
			if (lockRole != nullptr && state != ROLE_DEAD)
			{
				//���Ӣ����ʵ���ܻ����������ʵ�Ĺ������غ�
				if (getRealRect(this, property->getHitRect()).intersectsRect
				(lockRole->getRealRect(lockRole, property->getGetHitRect())))
				{
					//֤��������,����ƮѪ�ķ���
					int atk = property->getATK();
					//��int����ת��Ϊconst char *���͵�����
					__String * hpStr = __String::createWithFormat("%d", atk);
					//���ñ�������ɫ�ĵ�Ѫ
					lockRole->fallHP(hpStr->getCString());
					//�޸�Hp
					lockRole->property->setHP(lockRole->property->getHP() - atk);
					//�ж��Ƿ�С�ڵ���0
					if (lockRole->property->getHP() <= 0)
					{
						lockRole->getBaseAI()->stopRoleAI();
						lockRole->getBaseFSM()->changeToDead();
					}
					
				}
			}

		}
		//����ʱ��ص�
		if (movementType == COMPLETE)
		{
			baseFSM->changeToDefault();
		}
	}
	//������Ż�������
	if (strcmp(movementID, "death") == 0)
	{
		//�ȶ�����������ͷ�
		if (movementType == COMPLETE)
		{
			//�ѽ�ɫ״̬�л���free
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
	//���������ľ��ο���ʼ��
	Rect realRect = Rect(rect.origin.x + role->getPositionX(),
		rect.origin.y + role->getPositionY(), rect.size.width,
		rect.size.height);

	//��������������ϵ������ľ���
	return realRect;
}

void BaseRole::fallHP(const char * hpCount)
{
	//�������󣬰�hpCout����
	FlyText * flyText = FlyText::create(hpCount);
	//��������
	flyText->startAnimation();
	//��ӵ��ڵ���
	this->addChild(flyText);
}

void BaseRole::purge()
{
	this->getBaseFSM()->purge();
	this->getBaseAI()->purge();
	//ɾ���Լ�
	removeFromParent();
}
