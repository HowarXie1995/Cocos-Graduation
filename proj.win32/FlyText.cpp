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
	//设置伤害动画
	//设置lab动画向上运动0.7秒内，在y方向，移动150像素 边动边隐藏
	auto easeIn = EaseExponentialIn::create(Spawn::create(MoveBy::create(.7f, 
		Vec2(0, 150)), FadeOut::create(.7), NULL));
	//回调函数
	auto sequence = Sequence::create(easeIn,		//执行运动
		CallFunc::create([&]() 
			{this->remove0bject(); }), NULL);	//调用removeObject方法
	label->runAction(sequence);
}

void FlyText::remove0bject()
{
	//当前动作全部停止
	stopAllActions();
	//删除所有的子节点
	removeAllChildrenWithCleanup(true);
	//删除对象
	this->removeFromParent();
}
