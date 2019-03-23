#include "MapLayer.h"

bool MapLayer::init()
{
	return true;
}

void MapLayer::setBackGronud(const char * filename)
{
	//判断是否为空
	if (bgImageView == nullptr)
	{
		//为空进行初始化
		bgImageView = ImageView::create();
		//修改锚点为00
		bgImageView->setAnchorPoint(Point::ZERO);
		//设置坐标
		bgImageView->setPosition(Point::ZERO);
		//加入当前
		this->addChild(bgImageView);
	}
	//如果不为空，直接加载纹理
	bgImageView->loadTexture(filename);
}
