/**�ļ�����BulletLayer.h
  *�������ӵ���ͷ�ļ�
  *���ܣ���Ϸ�зɻ����Ƿ����ӵ��Ŀ��ƣ����Է����ӵ���ֹͣ�����ӵ�
  */
#ifndef __R_BULLET_LAYER_H__
#define __R_BULLET_LAYER_H__
#include "cocos2d.h"

USING_NS_CC;

class BulletLayer : public CCLayer
{
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	virtual bool init();
	
	void addBullet(float dt);
	void bulletMoveFinished(CCNode* pSender);
	void startShoot(float delay=0);
	void stopShoot();
	void removeBullet(CCSprite* bullet);

	CCArray* m_pAllBullet;

private:
	CCSpriteBatchNode* bulletBatchNode;
};
#endif  //__R_BULLET_LAYER_H__