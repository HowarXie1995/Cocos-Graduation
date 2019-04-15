#ifndef __DataManager_h__
#define __DataManager_h__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SceneManager.h"

USING_NS_CC;
USING_NS_CC_MATH;

class DataManager
{
	//设置为单例类
public:
	static DataManager * getInstance();
	//初始化方法
	void initWithJsonFile(const char *filename);

	//返回容器的方法
	std::vector<std::string> getLevelDataArrayByIndex(int index);
public:
	//声明一个关卡信息的字符串变量
	std::string tollgateData;
	//保存单独关卡所包含的数据
	std::vector<std::string> _levelDataArray;
	//关卡编号
	CC_SYNTHESIZE(int, levelIndex, LevelIndex);


};

#endif // !__DataManager_h__
