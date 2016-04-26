/**�ļ�����Enemy.h
  *�������л�����ͷ�ļ�
  *���ܣ��л����࣬���Բ����л����󶨵л�ͼƬ�������л���������ȡ�л���������С
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