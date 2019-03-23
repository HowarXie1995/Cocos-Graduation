#ifndef __MapLayer_h__
#define __MapLayer_h__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class MapLayer:public Layer
{
public:
	CREATE_FUNC(MapLayer);
	virtual bool init();

	//�󶨱���ͼƬ�ķ���
	void setBackGronud(const char * filename);

private:
	ImageView * bgImageView;
};


#endif // !__MapLayer_h__
