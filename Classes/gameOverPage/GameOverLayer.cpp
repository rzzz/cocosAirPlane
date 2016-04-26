/**�ļ�����GameOverLayer.cpp
  *��������Ϸ����������ʵ���ļ�
  */
#include "GameOverLayer.h"
#include "../GameScene.h"
int GameOverLayer::highestHistoryScore = 0;

GameOverLayer::GameOverLayer()
{
	thisTimeGetscore = 0;
	passScoreItem = NULL;
}

GameOverLayer::~GameOverLayer()
{
}

GameOverLayer* GameOverLayer::create(int passScore)
{
	GameOverLayer *pRet = new GameOverLayer();  
	pRet->thisTimeGetscore = passScore;
	if (pRet && pRet->init())
	{   
		pRet->autorelease();   
	}   
	else
	{   
		delete pRet;   
		pRet = NULL;   
	}
	return pRet;
}

bool GameOverLayer::init()
{
	bool bRet = false;
	do
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSprite* gameOverBg = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
		gameOverBg->setPosition(ccp(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + visibleSize.height/2));
		this->addChild(gameOverBg);

		passScoreItem=CCLabelBMFont::create("0", "font/font.fnt");
		passScoreItem->setColor(ccc3(143, 146, 147));  //�Ұ�ɫ
		passScoreItem->setAnchorPoint(ccp(0.5, 0.5));
		passScoreItem->setPosition(ccp(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + visibleSize.height/2));
		CCString* strScore = CCString::createWithFormat("%d", this->thisTimeGetscore);  //��ʽ��Ϊ�ַ��� 
		passScoreItem->setString(strScore->m_sString.c_str());  //��CCString�л��char*,���·���
		this->addChild(passScoreItem);

		CCLabelTTF* highestScoreItem = CCLabelTTF::create("", "Arial", 24);
		highestScoreItem->setColor(ccc3(3, 3, 3));  //��ɫ
		CCString* highestScore=CCString::createWithFormat("highestScore:%d", GameOverLayer::highestHistoryScore);
		highestScoreItem->setString(highestScore->m_sString.c_str());
		highestScoreItem->setPosition(ccp(visibleOrigin.x + highestScoreItem->getContentSize().width/2,
										visibleOrigin.y + visibleSize.height - highestScoreItem->getContentSize().height));
		this->addChild(highestScoreItem);

		if (thisTimeGetscore > GameOverLayer::highestHistoryScore)
		{  
			CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", thisTimeGetscore);  //�޸Ĵ浵
			CCUserDefault::sharedUserDefault()->flush();
			GameOverLayer::highestHistoryScore = thisTimeGetscore;  //��߷������趨
		}

		CCDelayTime* delay = CCDelayTime::create(1.0f);  
		CCScaleTo* scaleBig = CCScaleTo::create(1.0f, 3.0f);  
		CCScaleTo* scaleLittle = CCScaleTo::create(0.3f, 2.0f);  
		CCFiniteTimeAction* sequence = CCSequence::create(delay, scaleBig, scaleLittle, NULL);
		passScoreItem->runAction(sequence);

		CCSprite* normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
		CCSprite* pressedPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
    	CCMenuItemImage* restartGame = CCMenuItemImage::create();
		restartGame->initWithNormalSprite(normalPause, pressedPause, NULL, this, menu_selector(GameOverLayer::restartGame));
		restartGame->setPosition(ccp(visibleOrigin.x + visibleSize.width - normalPause->getContentSize().width,
									 visibleOrigin.y + normalPause->getContentSize().height));

		CCMenu* menu = CCMenu::create(restartGame, NULL);
		menu->setPosition(CCPointZero);
		this->addChild(menu, 10);
		
		bRet = true;
	}while(0);

	return bRet;
}

void GameOverLayer::restartGame(CCObject* pSender)
{
	CCScene *pGameScene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(pGameScene);
}

void GameOverLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();  //������Ϸ
}

void GameOverLayer::keyMenuClicked()
{
	//CCDirector::sharedDirector()  to do other things
}