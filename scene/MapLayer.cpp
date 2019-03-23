#include "MapLayer.h"

bool MapLayer::init()
{
	return true;
}

void MapLayer::setBackGronud(const char * filename)
{
	//�ж��Ƿ�Ϊ��
	if (bgImageView == nullptr)
	{
		//Ϊ�ս��г�ʼ��
		bgImageView = ImageView::create();
		//�޸�ê��Ϊ00
		bgImageView->setAnchorPoint(Point::ZERO);
		//��������
		bgImageView->setPosition(Point::ZERO);
		//���뵱ǰ
		this->addChild(bgImageView);
	}
	//�����Ϊ�գ�ֱ�Ӽ�������
	bgImageView->loadTexture(filename);
}
