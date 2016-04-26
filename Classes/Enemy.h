/**文件名：Enemy.h
  *描述：敌机父类头文件
  *功能：敌机父类，可以产生敌机，绑定敌机图片，操作敌机生命，获取敌机外观区域大小
  */
#ifndef __R_ENEMY_H__
#define __R_ENEMY_H__
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public CCNode
{
public:
	Enemy();
	~Enemy();
	Enemy* create();
	void bindSprite(CCSprite* sprite, int life);
	CCSprite* getSprite();
	int getLife();
	void loseLife(int num=1);
	CCRect getBoundingBox();

private:
	CCSprite* m_sprite;
	int m_life;
};
#endif  //__R_ENEMY_H__