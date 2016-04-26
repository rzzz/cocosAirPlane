/**文件名：BulletLayer.cpp
  *描述：子弹层头文件
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

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");//TexturePacker打包得到
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
	float bulletSpeed = 210 / 1;//飞行速度，210像素每秒
	float moveTime = length / bulletSpeed;//飞行时间
	auto moveAction = CCMoveTo::create(moveTime, ccp(bulletPosition.x,
						CCDirector::sharedDirector()->getVisibleSize().height + bullet->getContentSize().height));
	//CCCallFuncN可以回调一个只带一个参数的方法，这个参数为消息发送者
	auto actionDone = CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));
	auto sequence = CCSequence::create(moveAction, actionDone, NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(CCNode* pSender)
{
	if(pSender)
	{
		CCSprite* bullet = (CCSprite*)pSender;
		m_pAllBullet->removeObject(bullet);//移除CCArray
		this->bulletBatchNode->removeChild(bullet,true);//移除屏幕
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