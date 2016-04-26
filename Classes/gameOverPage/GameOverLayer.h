/**�ļ�����GameOverLayer.h
  *��������Ϸ����������ͷ�ļ�
  *���ܣ���Ϸ���������㣬��ʾ������Ϸ�÷ֺ������ʷ�ɼ������������ʷ�ɼ�
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
	
	virtual void keyBackClicked();  //��Ӧback��
	virtual void keyMenuClicked();  //��Ӧhome��

	static int highestHistoryScore;
	
private:
	CCLabelBMFont* passScoreItem;
	int thisTimeGetscore;
};
#endif  //__R_GAMEOVER_LAYER_H__