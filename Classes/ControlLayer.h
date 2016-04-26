/**文件名：ControlLayer.h
  *描述：游戏控制层头文件
  *功能：游戏控制层，负责显示暂停开始按钮，当前分数
  */
#ifndef __R_CONTROL_LAYER__
#define __R_CONTROL_LAYER__
#include "cocos2d.h"

USING_NS_CC;

class ControlLayer : public CCLayer
{
public:
	CREATE_FUNC(ControlLayer);
	virtual bool init();
	
	void menuPauseCallBack(CCObject* pSender);
	void updateScore(int score);

private:
	CCMenuItemImage* pPauseItem;
	CCLabelBMFont* scoreItem;
	int MAX_SCORE;
};
#endif  //__R_CONTROL_LAYER__