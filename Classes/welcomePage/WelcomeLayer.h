/**�ļ�����WelcomeLayer.h
  *������Ӧ�ý����Ļ�ӭ���泡����ͷ�ļ�
  *���ܣ����ض�������ͼƬ��Դ����ʾ��ӭ���涯������������������Ϸ����
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