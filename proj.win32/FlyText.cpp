#include "FlyText.h"

FlyText * FlyText::create(const char * str)
{
	FlyText * flyText = new FlyText();
	if (flyText && flyText->init(str))
	{
		flyText->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(flyText);
	}
	return flyText;
}

bool FlyText::init(const char * str)
{
	label = Label::createWithTTF(str, "fonts/white.ttf", 30);
	label->setColor(Color3B::RED);
	this->addChild(label);
	return true;
}

void FlyText::startAnimation()
{
	//�����˺�����
	//����lab���������˶�0.7���ڣ���y�����ƶ�150���� �߶�������
	auto easeIn = EaseExponentialIn::create(Spawn::create(MoveBy::create(.7f, 
		Vec2(0, 150)), FadeOut::create(.7), NULL));
	//�ص�����
	auto sequence = Sequence::create(easeIn,		//ִ���˶�
		CallFunc::create([&]() 
			{this->remove0bject(); }), NULL);	//����removeObject����
	label->runAction(sequence);
}

void FlyText::remove0bject()
{
	//��ǰ����ȫ��ֹͣ
	stopAllActions();
	//ɾ�����е��ӽڵ�
	removeAllChildrenWithCleanup(true);
	//ɾ������
	this->removeFromParent();
}
