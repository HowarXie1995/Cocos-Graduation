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
	//����Ϊ������
public:
	static DataManager * getInstance();
	//��ʼ������
	void initWithJsonFile(const char *filename);

	//���������ķ���
	std::vector<std::string> getLevelDataArrayByIndex(int index);
public:
	//����һ���ؿ���Ϣ���ַ�������
	std::string tollgateData;
	//���浥���ؿ�������������
	std::vector<std::string> _levelDataArray;
	//�ؿ����
	CC_SYNTHESIZE(int, levelIndex, LevelIndex);


};

#endif // !__DataManager_h__
