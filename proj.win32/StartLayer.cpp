#include "StartLayer.h"


//������ת��utf-8��ʽ���
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32

bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//��õ�ǰ��Ļ��С
	Get_Screen_winSize;

	//����һ�����ر�ǩ
	Label * label = Label::createWithTTF("�ܾúܾ���ǰ...",	//��ǩ����
		"fonts/white.ttf",			//����
		45);						//�����С
	label->setPosition(Vec2(winSize.width /2, winSize.height /2));
	this->addChild(label);

	return true;
}
