#include "SceneManager.h"
#include "MenuLayer.h"
#include "LoadLayer.h"
#include "ControlLayer.h"



void SceneManager::goStartScene()
{
	//创建开始场景
	startScene = Scene::create();
	//创建层
	auto menuLayer = MenuLayer::create();
	//让层的场景管理指针指向这个
	menuLayer->tsm = this;					//指向当前类的对象
	//加入子场景
	startScene->addChild(menuLayer);
	Director::getInstance()->replaceScene(startScene);

}

void SceneManager::goGameScene()
{
	//创建游戏场景
	gameScene = Scene::create();
	//创建游戏层
	ControlLayer * controlLayer = ControlLayer::create();
	//让层的管理指针指向这个
	controlLayer->tsm = this;
	//加入子场景
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
