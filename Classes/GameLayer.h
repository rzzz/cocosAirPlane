/**�ļ�����GameLayer.h
  *��������Ϸ��������ͷ�ļ�
  *���ܣ���Ϸ���㣬��������ӷɻ����ǲ㣬�ӵ��㣬�л��㣬���Ʋ㣬�������ײ��⣬��Ϸ�߼�����
  */
#ifndef __R_GAME_LAYER_H__
#define __R_GAME_LAYER_H__
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"

USING_NS_CC;

class GameLayer : public CCLayer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init();
	virtual void update(float dt);
	void backgroundMove(float dt);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void keyBackClicked();//��Ӧback��
	virtual void keyMenuClicked();//��Ӧhome��

private:
	CCSprite* background1;//ѭ����������������ͼ�߶ȸ����ֻ���Ļ�߶�
	CCSprite* background2;
	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
	EnemyLayer* enemyLayer;
	ControlLayer* controlLayer;
	int thisTimeScore;
};
#endif //__R_GAME_LAYER_H__