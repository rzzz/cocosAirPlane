/**�ļ�����EnemyLayer.h
  *�������л���ͷ�ļ�
  *���ܣ��л��㣬�����л����Ƴ������Ƶл��ı�ըЧ��
  */
#ifndef __R_ENEMY_LAYER_H__
#define __R_ENEMY_LAYER_H__
#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

class EnemyLayer : public Enemy
{
public:
	EnemyLayer();
	~EnemyLayer();
	void startEnemy(int which);
	void stopEnemy();
	void addEnemy1(float dt);
	void enemy1Blowup(Enemy* enemy1);
	void enemy1Remove(CCNode* pSender, void* data);
	void enemy1MoveFinished(CCNode* pSender);
	//void removeAlllEnemy();
	CCArray* m_pAllEnemy1;
private:
	const int ENEMY1_MAXLIFE;
	int enemy1Speed;
};
#endif //__R_ENEMY_LAYER_H__