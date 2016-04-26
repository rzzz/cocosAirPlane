/**�ļ�����ControlLayer.h
  *��������Ϸ���Ʋ�ͷ�ļ�
  *���ܣ���Ϸ���Ʋ㣬������ʾ��ͣ��ʼ��ť����ǰ����
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