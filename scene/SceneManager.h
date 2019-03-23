#ifndef __SceneManager_h__
#define __SceneManager_h__

#include <iostream>
#include "cocos2d.h"
#include "tools_define.h"
USING_NS_CC;

class SceneManager
{
public:		//��Ա����
	Scene * loadScene;		//���س���
	Scene * startScene;		//��ʼ����
	Scene * gameScene;		//��Ϸ����
public:		/*��Ա����*/
//�������ƣ�goStartScene
//���������
//���������
//�������ܣ���ת��Ϸ��ʼ����
//ע�����
	void  goStartScene();		//��ת��Ϸ��ʼ�����ķ���

//�������ƣ�goGameScene
//���������
//���������
//�������ܣ���ת��Ϸ�����ķ���
//ע�����
	void  goGameScene();		//��ת��Ϸ�����ķ���

//�������ƣ�createLoadScene
//���������
//���������
//�������ܣ���ת���س����ķ���
//ע�����
	void  createLoadScene();		//��ת���س����ķ���
		
};

#endif // !__SceneManager_h__

