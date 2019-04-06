#ifndef __HRocker_h__
#define __HRocker_h__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

//���ڱ�ʶҡ�˻���ҡ�˵ı���
typedef enum
{
	tag_rocker,			//��ʶҡ��
	tag_rockerBG		//ҡ�˵�����
}tagForHRocker;

//
typedef enum
{
	rocker_stay = 0,	//Ĭ��״̬
	rocker_right,		//���� = 1
	rocker_up,			//�� = 2
	rocker_left,		//�� = 3
	rocker_down,		//�� = 4
}tagDirection;



class HRocker:public Layer
{
public:
	CREATE_FUNC(HRocker);
//�������ƣ�createHRocker
//���������
	//rockerImageName:ҡ�˵���Դ����
	//rockerBGImageName:ҡ�˵���Դ����
	//position:ҡ�˵�����
//���������HRocker��Ķ���
//�������ܣ���������
//ע�����
	static HRocker * createHRocker(const char * rockerImageName,	//ҡ����Դ����
		const char * rockerBGImageName,								//������Դ����
		Vec2 position);												//ҡ�˵�����

//�������ƣ�startRocker
//���������
//���������_isStopOther
//�������ܣ�����ҡ�˵ķ���
//ע�����
	void startRoker(bool _isStopOther);

//�������ƣ�stopRocker
//���������
//���������HRocker��Ķ���
//�������ܣ�ȡ��ҡ�˵ļ���
//ע�����
	void stopRocker();

//�������ƣ�stopRocker
//���������
//���������HRocker��Ķ���
//�������ܣ�ȡ��ҡ�˵ļ���
//ע�����
	Vec2 getAnglePostion(float r, float angle);


	int rockerDirection;			//ҡ�˵ķ���

public:	//��Ա����
	bool rockerRun;		//�ж�����ķ���


private://˽�м̳�

//�������ƣ�rockerInit
//���������
//���������
//�������ܣ���ʼ������
//ע�����

	void rockerInit(const char * rockerImageName,	//ҡ�˵�����
		const char * rockerBGImageName,		//ҡ�˱���
		Vec2 position);		//��������

	bool isCanMove;			//��־ҡ���Ƿ��ܲ���
	//
//�������ƣ�rockerInit
//���������
//���������
//�������ܣ���ȡ��ǰҡ�ˣ����û������Ƕȵ�����
//ע�����
	float getRad(Vec2 pos1, Vec2 pos2);


	Vec2 rockerBGPosition;			//����ҡ�˵ı�������
	float rockerBGR;				//����ҡ�˵ı����뾶

	//�����¼��Ļص�����
	bool onTouchBegan(Touch * touch, Event * unused_event);
	void onTouchMoved(Touch * touch, Event * unused_event);
	void onTouchEnded(Touch * touch, Event * unused_event);
};

#endif // !__HRocker_h__
