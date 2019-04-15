#include "HRocker.h"

#define PI 3.1415926

HRocker * HRocker::createHRocker(const char * rockerImageName, const char * rockerBGImageName, Vec2 position)
{
	//����һ��Rocker����
	HRocker * layer = HRocker::create();
	//����㴴���ɹ���ִ�г�ʼ������
	if (layer)
	{
		//�����ɹ�
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	//����ʧ��
	CC_SAFE_DELETE(layer);
	
	return nullptr;
}



void HRocker::rockerInit(const char * rockerImageName, const char * rockerBGImageName, Vec2 position)
{
	//����һ����������
	auto spRockerBG = Sprite::create(rockerBGImageName);
	//���ñ������������
	spRockerBG->setPosition(position);
	//����ҡ�˱���
	spRockerBG->setVisible(false);
	this->addChild(spRockerBG, 0, tag_rockerBG);

	//����ҡ�˾���
	auto spRocker = Sprite::create(rockerImageName);
	//���þ��������
	spRocker->setPosition(position);
	//����ҡ��
	spRocker->setVisible(false);
	this->addChild(spRocker, 0, tag_rocker);

	//����λ��
	rockerBGPosition = position;
	//�뾶
	rockerBGR = spRockerBG->getContentSize().width / 2;
	//�������
	rockerDirection = -1;
	//����ҡ���Ƿ������ָ
	isCanMove = true;


}



void HRocker::startRoker(bool _isStopOther)
{
	//����һ��ҡ��
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	//����һ��ҡ�˱���
	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

	//����һ������ϵ��ʵ�ִ����¼�
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	//��ʼ
	touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	//�ƶ���
	touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	//����
	touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	//�����¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	

}

void HRocker::stopRocker()
{
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	//���¼��ַ���ɾ����
	_eventDispatcher->removeEventListenersForTarget(this);

}

//
Vec2 HRocker::getAnglePostion(float r, float angle)
{
	return Vec2(r*cos(angle), r*sin(angle));
}


bool HRocker::onTouchBegan(Touch * touch, Event * unused_event)
{
	//��ȡcocos������ϵ
	Vec2 point = touch->getLocation();
	//�õ�rocker�Ķ���
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);

	//��ε��Ƿ���rocker��������
		//�����
	if (rocker->getBoundingBox().containsPoint(point))
	{
		//�������Բ����
		isCanMove = true;
		//��ӡ���
		log("begin");
	}


	return true;
}


float HRocker::getRad(Vec2 pos1, Vec2 pos2)
{
	//����������xyƫ����
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//�õ�����֮��x��y����
	float x = px2 - px1;
	float y = py2 - py1;

	//���б�ߵĳ���:x2+y2 �ٿ�ƽ��
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	//����Ƕ�����ֵ
	float cosAngle = x / xie;
	//���Ǻ���
	float rad = acos(cosAngle);
	
	//ȡ����ȡֵ��0��-180��
	if (py2 < py1)
	{
		rad = -rad;
	}

	return rad;
}


void HRocker::onTouchMoved(Touch * touch, Event * unused_event)
{
	//�ж��Ƿ����������
		//���Ϊ�٣�ֱ�ӷ���
	if (!isCanMove)
	{
		return;
	}
		//���Ϊ�棬����ִ��
	//��ȡ�����������
	Vec2 point = touch->getLocation();
	//��ȡ��rocker�Ķ���
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	//��ȡ�Ƕȵķ���
	float angle = getRad(rockerBGPosition, point);
	//�ж�Բ�ľ��Ƿ����ҡ�˱����뾶
	if (sqrt(pow(rockerBGPosition.x - point.x, 2) +
		pow(rockerBGPosition.y - point.y, 2)) >= rockerBGR)
	{	//�������:��ָ�Ƴ�������
		rocker->setPosition(ccpAdd(getAnglePostion(rockerBGR, angle),
			rockerBGPosition));
	}
	else//ҡ�˸�����ָ�ƶ�
	{
		rocker->setPosition(point);
	}
	//���������-4/pi �� 4/pi֮��
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
	//��ȡ�������飬���ָ���ԭ����λ��
	auto rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	auto rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);
	//ֹͣ���е��˶�
	rocker->stopAllActions();
	//��0.08��֮���ƶ���ָ��λ��
	rocker->runAction(MoveTo::create(0.08f, rockerBGPosition));
	isCanMove = false;
	//�ƶ����ʼλ��
	rockerDirection = rocker_stay;

}
