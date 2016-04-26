/**文件名：WelcomeLayer.h
  *描述：应用进入后的欢迎界面场景层头文件
  *功能：加载动画所需图片资源，显示欢迎界面动画，动画结束进入游戏场景
  */
#ifndef __R_WELCOME_LAYER_H__
#define __R_WELCOME_LAYER_H__
#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer : public CCLayer
{
public:
	CREATE_FUNC(WelcomeLayer);
	virtual bool init();
	
	void loadingDone();
	bool isHaveSaveFile();
	void getHighestHistorySorce();
};
#endif  //__R_WELCOME_LAYER_H__