/**文件名：EnemyLayer.cpp
  *描述：敌机层实现文件
  */
#include "EnemyLayer.h"

EnemyLayer::EnemyLayer():ENEMY1_MAXLIFE(2)
{
	m_pAllEnemy1 = CCArray::create();
	m_pAllEnemy1->retain();
	enemy1Speed = 250 / 1;
}

EnemyLayer::~EnemyLayer()
{
	m_pAllEnemy1->release();
	m_pAllEnemy1 = NULL;
}

void EnemyLayer::startEnemy(int which)
{
	switch(which)
	{
		case 1:
			this->schedule(schedule_selector(EnemyLayer::addEnemy1), 1.2f, kCCRepeatForever, 1);
			break;
		default:
			break;
	}
}

void EnemyLayer::stopEnemy()
{
	this->unschedule(schedule_selector(EnemyLayer::addEnemy1));
}

void EnemyLayer::addEnemy1(float dt)
{
	Enemy* enemy1 = Enemy::create();//此处为调用父类的方法，不然直接类名::方法这种方式只能调用静态方法
	enemy1->bindSprite(CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png")), ENEMY1_MAXLIFE);
	//随机初始位置
	CCSize enemy1Size = enemy1->getSprite()->getContentSize();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	int minX = enemy1Size.width / 2;
	int maxX = visibleSize.width - enemy1Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;
	enemy1->setPosition(ccp(actualX, visibleSize.height + enemy1Size.height/2 + 10));
	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

	//随机飞行速度  
	//float minDuration,maxDuration;  
	//根据游戏难度给minDuration,maxDuration赋值  
	//int rangeDuration = maxDuration - minDuration;  
	//int actualDuration = (rand() % rangeDuration) + minDuration; 
	CCPoint destPoint = CCPoint(actualX, 0 - enemy1->getSprite()->getContentSize().height/2 - 10);
	float moveTime=(enemy1->getPosition().y - destPoint.y) / enemy1Speed;
	auto moveAction = CCMoveTo::create(moveTime, destPoint);
	auto actionDone = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemy1MoveFinished));
	auto sequence = CCSequence::create(moveAction, actionDone, NULL);
	enemy1->runAction(sequence);
}

void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
	auto sp1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png");
	auto sp2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png");
	auto sp3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png");
	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(0.2f);  
	animation->addSpriteFrame(sp1);  
	animation->addSpriteFrame(sp2);
	animation->addSpriteFrame(sp3);
	CCAnimate* animate = CCAnimate::create(animation); 
	//CCCallFuncND可以回调一个带两个参数的方法，这个参数为消息发送者和自定义附带消息
	auto removeEnemy1 = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::enemy1Remove), (void*)enemy1);
	auto sequence = CCSequence::create(animate, removeEnemy1, NULL);
	enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::enemy1MoveFinished(CCNode* pSender)
{
	if(pSender)
	{
		CCNode* enemy1 = (CCNode*)pSender;
		m_pAllEnemy1->removeObject(enemy1);  //移除CCArray
		this->removeChild(enemy1, true);  //移除屏幕
	}
}

void EnemyLayer::enemy1Remove(CCNode* pSender, void* data)
{
	Enemy* enemy1 = (Enemy*)data;
	if(pSender && enemy1)
	{
		m_pAllEnemy1->removeObject(enemy1);
		this->removeChild(enemy1, true);
	}
}