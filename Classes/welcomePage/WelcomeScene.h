/**文件名：WelcomeScene.h
  *描述：应用进入后的欢迎界面场景头文件
  *功能：创建并添加一个WelcomeLayer层到此场景
  */
#ifndef __R_WELCOME_SCENE_H__
#define __R_WELCOME_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public CCScene
{
public:
	CREATE_FUNC(WelcomeScene);
	virtual bool init();
};
#endif  //__R_WELCOME_SCENE_H__