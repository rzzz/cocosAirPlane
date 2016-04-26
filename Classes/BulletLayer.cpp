/**�ļ�����BulletLayer.cpp
  *�������ӵ���ͷ�ļ�
  */
#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer()
{
	m_pAllBullet = CCArray::create();
	m_pAllBullet->retain();
}

BulletLayer::~BulletLayer()
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}

bool BulletLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");//TexturePacker����õ�
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(bulletBatchNode);

		bRet = true;
	}while(0);

	return bRet;
}

void BulletLayer::addBullet(float dt)
{
	CCSprite* bullet = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet1.png"));
	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(PlaneLayer::AIRPLANE)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x,
						planePosition.y+PlaneLayer::sharedPlane->getChildByTag(PlaneLayer::AIRPLANE)->getContentSize().height/2 + 15);
	bullet->setPosition(bulletPosition);
	bulletBatchNode->addChild(bullet);
	m_pAllBullet->addObject(bullet);
	float length = CCDirector::sharedDirector()->getVisibleSize().height - bulletPosition.y + bullet->getContentSize().height/2;
	float bulletSpeed = 210 / 1;//�����ٶȣ�210����ÿ��
	float moveTime = length / bulletSpeed;//����ʱ��
	auto moveAction = CCMoveTo::create(moveTime, ccp(bulletPosition.x,
						CCDirector::sharedDirector()->getVisibleSize().height + bullet->getContentSize().height));
	//CCCallFuncN���Իص�һ��ֻ��һ�������ķ������������Ϊ��Ϣ������
	auto actionDone = CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));
	auto sequence = CCSequence::create(moveAction, actionDone, NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(CCNode* pSender)
{
	if(pSender)
	{
		CCSprite* bullet = (CCSprite*)pSender;
		m_pAllBullet->removeObject(bullet);//�Ƴ�CCArray
		this->bulletBatchNode->removeChild(bullet,true);//�Ƴ���Ļ
	}
}

void BulletLayer::startShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kCCRepeatForever, delay);
}

void BulletLayer::stopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(CCSprite* bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet, true);
	}
}