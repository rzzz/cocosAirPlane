/**�ļ�����WelcomeLayer.cpp
*������Ӧ�ý����Ļ�ӭ���泡����ʵ���ļ�
*/
#include "WelcomeLayer.h"
#include "../GameScene.h"
#include "../gameOverPage/GameOverLayer.h"

bool WelcomeLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");  
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");
		getHighestHistorySorce();

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCSprite* welcomeBackground = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		welcomeBackground->setPosition(ccp(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + visibleSize.height/2));
		this->addChild(welcomeBackground);

		CCSprite* loading = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		loading->setPosition(ccp(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + visibleSize.height/2));
		this->addChild(loading);

		CCAnimation* animation=CCAnimation::create();//loading��֡����  
		animation->setDelayPerUnit(0.2f);  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));  
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));  
		CCAnimate* animate = CCAnimate::create(animation);  
		CCRepeat* repeat = CCRepeat::create(animate, 2);//�����ظ�2��  
		CCDelayTime* wait = CCDelayTime::create(0.5f);
		CCCallFunc* repeatDone=CCCallFunc::create(this,callfunc_selector(WelcomeLayer::loadingDone));//loadingDone����ת����������Ϸ����
		auto sequence = CCSequence::create(wait, repeat, wait, repeatDone, NULL);
		loading->runAction(sequence); 

		bRet = true;
	}while(0);

	return bRet;
}

void WelcomeLayer::loadingDone()
{
	CCScene* pGameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(pGameScene);
}

bool WelcomeLayer::isHaveSaveFile()
{  
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		//ͨ�����õ�bool�ͱ�־λ�ж�
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);//д��bool�ж�λ
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", 0);//д���ʼ����0
		CCUserDefault::sharedUserDefault()->flush();//������һ��Ҫ����flush�����ܴӻ���д��io
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::getHighestHistorySorce()
{
	if (isHaveSaveFile())
	{
		GameOverLayer::highestHistoryScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);//��ȡ��ʷ��߷�
	}
}