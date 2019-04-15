#ifndef __DialogLayer_h__
#define __DialogLayer_h__
#include <iostream>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class DialogLayer:public Layer
{
public:
	//��������ķ���
	static DialogLayer *createWithJsonFile(const char * filename);

	bool init(std::string str);
	//ˢ�µĺ���
	void MultUpdate(float dt);
	//��ȡ���ݵķ���
	void getDataByIndex(int idx);
	//��ʾ�������ֵķ���
	void showAllContent();
	//��ʼ��cocostudio�����ķ���
	void initStudioScene(const char * csbFile);
	//��������Ļص�����
	void touchDownAction(Ref * sender, Widget::TouchEventType controlEvent);
private:
	bool _isOver;		//�����Ļ�ϵ��ַ����Ƿ���ʾ��ȫ
	int index;			//���
	
	std::string conversation;		//�������������ַ���
	std::vector<std::string> _conVector;	//���е���Ϣ

	Text * speetch;		//����˵������
	Text * name;		//��������

	std::string mStr;		//�������������ַ���
	std::string tempStr;		//����ƴ��ʹ�õ��ַ���
	std::vector<std::string>strVector;	//�����ַ���������
	int vecLength;		//�����ĳ���
};

#endif // !__DialogLayer_h__
