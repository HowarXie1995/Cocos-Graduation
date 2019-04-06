#ifndef __HRocker_h__
#define __HRocker_h__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

//用于标识摇杆还有摇杆的背景
typedef enum
{
	tag_rocker,			//标识摇杆
	tag_rockerBG		//摇杆的类型
}tagForHRocker;

//
typedef enum
{
	rocker_stay = 0,	//默认状态
	rocker_right,		//右走 = 1
	rocker_up,			//上 = 2
	rocker_left,		//左 = 3
	rocker_down,		//下 = 4
}tagDirection;



class HRocker:public Layer
{
public:
	CREATE_FUNC(HRocker);
//函数名称：createHRocker
//输入参数：
	//rockerImageName:摇杆的资源名字
	//rockerBGImageName:摇杆的资源名字
	//position:摇杆的坐标
//输出参数：HRocker类的对象
//函数功能：创建对象
//注意事项：
	static HRocker * createHRocker(const char * rockerImageName,	//摇杆资源名字
		const char * rockerBGImageName,								//背景资源名字
		Vec2 position);												//摇杆的坐标

//函数名称：startRocker
//输入参数：
//输出参数：_isStopOther
//函数功能：启动摇杆的方法
//注意事项：
	void startRoker(bool _isStopOther);

//函数名称：stopRocker
//输入参数：
//输出参数：HRocker类的对象
//函数功能：取消摇杆的监听
//注意事项：
	void stopRocker();

//函数名称：stopRocker
//输入参数：
//输出参数：HRocker类的对象
//函数功能：取消摇杆的监听
//注意事项：
	Vec2 getAnglePostion(float r, float angle);


	int rockerDirection;			//摇杆的方向

public:	//成员变量
	bool rockerRun;		//判断人物的方向


private://私有继承

//函数名称：rockerInit
//输入参数：
//输出参数：
//函数功能：初始化函数
//注意事项：

	void rockerInit(const char * rockerImageName,	//摇杆的名字
		const char * rockerBGImageName,		//摇杆背景
		Vec2 position);		//人物坐标

	bool isCanMove;			//标志摇杆是否能操作
	//
//函数名称：rockerInit
//输入参数：
//输出参数：
//函数功能：获取当前摇杆，和用户触摸角度的坐标
//注意事项：
	float getRad(Vec2 pos1, Vec2 pos2);


	Vec2 rockerBGPosition;			//保存摇杆的背景坐标
	float rockerBGR;				//保存摇杆的背景半径

	//触摸事件的回调方法
	bool onTouchBegan(Touch * touch, Event * unused_event);
	void onTouchMoved(Touch * touch, Event * unused_event);
	void onTouchEnded(Touch * touch, Event * unused_event);
};

#endif // !__HRocker_h__
