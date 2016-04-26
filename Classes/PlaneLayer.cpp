/**文件名：PlaneLayer.cpp
  *描述：游戏飞机主角层实现文件
  */
#include "PlaneLayer.h"
#include "gameOverPage/GameOverScene.h"

PlaneLayer* PlaneLayer::sharedPlane = NULL;
const int PlaneLayer::AIRPLANE = 88;

PlaneLayer::PlaneLayer()
{
}

PlaneLayer::~PlaneLayer()
{
}

PlaneLayer* PlaneLayer::create()
{
	PlaneLayer *pRet = new PlaneLayer();
	if(pRet && pRet->init())
	{
		pRet->autorelease();
		sharedPlane = pRet;
		return pRet;
	}
	else
	{
		delete pRet;
		return NULL;
	}
}

bool PlaneLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		isAlive = true;
		passScore = 0;
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSprite* plane = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		plane->setPosition(ccp(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + plane->getContentSize().height/2));
		this->addChild(plane, 0, AIRPLANE);

		auto blink = CCBlink::create(1, 3);
		auto animation = CCAnimation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
		auto animate = CCAnimate::create(animation);
		plane->runAction(blink);
		plane->runAction(animate);

		bRet = true;
	}while(0);

	return bRet;
}

void PlaneLayer::moveTo(CCPoint location)
{
	if(isAlive && !CCDirector::sharedDirector()->isPaused())
	{
		CCPoint actualPoint;  
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
		CCSize planeSize = this->getChildByTag(AIRPLANE)->getContentSize();  
		if (location.x < planeSize.width/2)
		{  
			location.x = planeSize.width / 2;  
		}  
		if (location.x > visibleSize.width - planeSize.width/2)
		{  
			location.x = visibleSize.width - planeSize.width/2;  
		}  
		if (location.y < planeSize.height/2)
		{  
			location.y = planeSize.height/2;  
		}  
		if (location.y > visibleSize.height - planeSize.height/2)
		{  
			location.y = visibleSize.height - planeSize.height/2;  
		}

		this->getChildByTag(AIRPLANE)->setPosition(location);  
	}
}

void PlaneLayer::gameOver(int passScore)
{
	auto sp1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png");
	auto sp2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png");
	auto sp3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png");
	auto sp4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png");
	auto animation = CCAnimation::create();
	animation->setDelayPerUnit(0.3f);  
	animation->addSpriteFrame(sp1);  
	animation->addSpriteFrame(sp2);
	animation->addSpriteFrame(sp3);
	animation->addSpriteFrame(sp4);
	CCAnimate* animate=CCAnimate::create(animation); 
	auto transScene = CCCallFunc::create(this, callfunc_selector(PlaneLayer::transGameOverScene));
	this->passScore = passScore;
	auto sequence = CCSequence::create(animate, transScene, NULL);	
	this->getChildByTag(AIRPLANE)->runAction(sequence);
	isAlive = false;
}

void PlaneLayer::transGameOverScene()
{
	CCScene *pGameOverScene = new GameOverScene(passScore);
	pGameOverScene->autorelease();
	CCDirector::sharedDirector()->replaceScene(pGameOverScene);
}