#include "HRocker.h"

#define PI 3.1415926

HRocker * HRocker::createHRocker(const char * rockerImageName, const char * rockerBGImageName, Vec2 position)
{
	//创建一个Rocker对象
	HRocker * layer = HRocker::create();
	//如果层创建成功就执行初始化方法
	if (layer)
	{
		//创建成功
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	//创建失败
	CC_SAFE_DELETE(layer);
	
	return nullptr;
}



void HRocker::rockerInit(const char * rockerImageName, const char * rockerBGImageName, Vec2 position)
{
	//创建一个背景精灵
	auto spRockerBG = Sprite::create(rockerBGImageName);
	//设置背景精灵的坐标
	spRockerBG->setPosition(position);
	//隐藏摇杆背景
	spRockerBG->setVisible(false);
	this->addChild(spRockerBG, 0, tag_rockerBG);

	//创建摇杆精灵
	auto spRocker = Sprite::create(rockerImageName);
	//设置精灵的坐标
	spRocker->setPosition(position);
	//隐藏摇杆
	spRocker->setVisible(false);
	this->addChild(spRocker, 0, tag_rocker);

	//背景位置
	rockerBGPosition = position;
	//半径
	rockerBGR = spRockerBG->getContentSize().width / 2;
	//方向变量
	rockerDirection = -1;
	//设置摇杆是否跟随手指
	isCanMove = true;


}



void HRocker::startRoker(bool _isStopOther)
{
	//创建一个摇杆
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	//创建一个摇杆背景
	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

	//创建一个精灵系，实现触摸事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	//开始
	touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	//移动中
	touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	//结束
	touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	//加入事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	

}

void HRocker::stopRocker()
{
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	//从事件分发器删除掉
	_eventDispatcher->removeEventListenersForTarget(this);

}

//
Vec2 HRocker::getAnglePostion(float r, float angle)
{
	return Vec2(r*cos(angle), r*sin(angle));
}


bool HRocker::onTouchBegan(Touch * touch, Event * unused_event)
{
	//获取cocos的坐标系
	Vec2 point = touch->getLocation();
	//得到rocker的对象
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);

	//半段点是否在rocker区域里面
		//如果是
	if (rocker->getBoundingBox().containsPoint(point))
	{
		//如果点在圆心内
		isCanMove = true;
		//打印输出
		log("begin");
	}


	return true;
}


float HRocker::getRad(Vec2 pos1, Vec2 pos2)
{
	//两个向量的xy偏移量
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//得到两点之间x、y距离
	float x = px2 - px1;
	float y = py2 - py1;

	//算出斜边的长度:x2+y2 再开平方
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	//算出角度余弦值
	float cosAngle = x / xie;
	//三角函数
	float rad = acos(cosAngle);
	
	//取反：取值到0到-180度
	if (py2 < py1)
	{
		rad = -rad;
	}

	return rad;
}


void HRocker::onTouchMoved(Touch * touch, Event * unused_event)
{
	//判断是否点在区域内
		//如果为假，直接返回
	if (!isCanMove)
	{
		return;
	}
		//如果为真，继续执行
	//获取触摸点的坐标
	Vec2 point = touch->getLocation();
	//获取到rocker的对象
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	//获取角度的方法
	float angle = getRad(rockerBGPosition, point);
	//判断圆心距是否大于摇杆背景半径
	if (sqrt(pow(rockerBGPosition.x - point.x, 2) +
		pow(rockerBGPosition.y - point.y, 2)) >= rockerBGR)
	{	//如果大于:手指移出背景外
		rocker->setPosition(ccpAdd(getAnglePostion(rockerBGR, angle),
			rockerBGPosition));
	}
	else//摇杆跟随手指移动
	{
		rocker->setPosition(point);
	}
	//如果弧度在-4/pi 到 4/pi之间
	if (angle >= -PI / 4 && angle < PI / 4)
	{
		rockerDirection = rocker_right;
		rockerRun = false;
	}
	else if (angle >= PI / 4 && angle < 3 * PI / 4)
	{
		rockerDirection = rocker_up;
	}
	else if ((angle >= 3 * PI / 4 && angle < PI) 
		|| (angle >= -PI && angle < -3*PI/4))
	{
		rockerDirection = rocker_left;
		rockerRun = true;
	}
	else if (angle >= -3 * PI / 4 && angle < -PI / 4)
	{
		rockerDirection = rocker_down;
	}
	
}

void HRocker::onTouchEnded(Touch * touch, Event * unused_event)
{
	if (!isCanMove)
	{
		return;
	}
	//获取两个精灵，并恢复到原来的位置
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);
	//停止所有的运动
	rocker->stopAllActions();
	//在0.08秒之类移动到指定位置
	rocker->runAction(MoveTo::create(0.08f, rockerBGPosition));
	isCanMove = false;
	//移动到最开始位置
	rockerDirection = rocker_stay;

}
