#ifndef __SceneManager_h__
#define __SceneManager_h__

#include <iostream>
#include "cocos2d.h"
#include "tools_define.h"
USING_NS_CC;

class SceneManager
{
public:		//成员变量
	Scene * loadScene;		//加载场景
	Scene * startScene;		//开始场景
	Scene * gameScene;		//游戏场景
public:		/*成员函数*/
//函数名称：goStartScene
//输入参数：
//输出参数：
//函数功能：跳转游戏开始场景
//注意事项：
	void  goStartScene();		//跳转游戏开始场景的方法

//函数名称：goGameScene
//输入参数：
//输出参数：
//函数功能：跳转游戏场景的方法
//注意事项：
	void  goGameScene();		//跳转游戏场景的方法

//函数名称：createLoadScene
//输入参数：
//输出参数：
//函数功能：跳转加载场景的方法
//注意事项：
	void  createLoadScene();		//跳转加载场景的方法
		
};

#endif // !__SceneManager_h__

