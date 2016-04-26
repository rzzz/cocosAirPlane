/**文件名：GameOverLayer.h
  *描述：游戏结束场景层头文件
  *功能：游戏结束场景层，显示本局游戏得分和最高历史成绩，更新最高历史成绩
  */
#ifndef __R_GAMEOVER_LAYER_H__
#define __R_GAMEOVER_LAYER_H__
#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public CCLayer
{
public:
	GameOverLayer();
	~GameOverLayer();
	static GameOverLayer* create(int passScore);
	virtual bool init();
	void restartGame(CCObject* pSender);
	
	virtual void keyBackClicked();  //对应back键
	virtual void keyMenuClicked();  //对应home键

	static int highestHistoryScore;
	
private:
	CCLabelBMFont* passScoreItem;
	int thisTimeGetscore;
};
#endif  //__R_GAMEOVER_LAYER_H__