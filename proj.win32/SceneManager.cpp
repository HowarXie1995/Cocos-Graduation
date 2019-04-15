#include "SceneManager.h"
#include "MenuLayer.h"
#include "LoadLayer.h"
#include "ControlLayer.h"



void SceneManager::goStartScene()
{
	//������ʼ����
	startScene = Scene::create();
	//������
	auto menuLayer = MenuLayer::create();
	//�ò�ĳ�������ָ��ָ�����
	menuLayer->tsm = this;					//ָ��ǰ��Ķ���
	//�����ӳ���
	startScene->addChild(menuLayer);
	Director::getInstance()->replaceScene(startScene);

}

void SceneManager::goGameScene()
{
	//������Ϸ����
	gameScene = Scene::create();
	//������Ϸ��
	ControlLayer * controlLayer = ControlLayer::create();
	//�ò�Ĺ���ָ��ָ�����
	controlLayer->tsm = this;
	//�����ӳ���
	gameScene->addChild(controlLayer);
	Director::getInstance()->replaceScene(gameScene);
}

void SceneManager::createLoadScene()
{
	loadScene = Scene::create();
	LoadLayer * loadlayer = LoadLayer::create();
	loadlayer->tsm = this;
	loadScene->addChild(loadlayer);
}
