/**文件名：GameLayer.h
  *描述：游戏主场景层头文件
  *功能：游戏主层，在其上添加飞机主角层，子弹层，敌机层，控制层，并完成碰撞检测，游戏逻辑控制
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

	virtual void keyBackClicked();//对应back键
	virtual void keyMenuClicked();//对应home键

private:
	CCSprite* background1;//循环背景简单做法：作图高度高于手机屏幕高度
	CCSprite* background2;
	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
	EnemyLayer* enemyLayer;
	ControlLayer* controlLayer;
	int thisTimeScore;
};
#endif //__R_GAME_LAYER_H__