/**�ļ�����ControlLayer.cpp
  *��������Ϸ���Ʋ�ʵ���ļ�
  */
#include "ControlLayer.h"

bool ControlLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		MAX_SCORE = 999999;
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCSprite* normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		CCSprite* pressedPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
		pPauseItem = CCMenuItemImage::create();
		pPauseItem->initWithNormalSprite(normalPause,pressedPause,NULL, this, menu_selector(ControlLayer::menuPauseCallBack));
		pPauseItem->setPosition(ccp(normalPause->getContentSize().width/2 + 10, visibleSize.height - normalPause->getContentSize().height/2 - 10));
		CCMenu* menuPause = CCMenu::create(pPauseItem, NULL);
		menuPause->setPosition(CCPointZero);
		this->addChild(menuPause);

		//�����Զ���������Դ
		scoreItem=CCLabelBMFont::create("0","font/font.fnt");
		scoreItem->setColor(ccc3(143, 146, 147));  //�Ұ�ɫ
		scoreItem->setAnchorPoint(ccp(0, 0.5));
		scoreItem->setPosition(ccp(pPauseItem->getPositionX() + normalPause->getContentSize().width, pPauseItem->getPositionY()));
		CCString* strScore=CCString::createWithFormat("%d", 0);  //��ʽ��Ϊ�ַ��� 
		scoreItem->setString(strScore->m_sString.c_str());  //��CCString�л��char*,���·���
		this->addChild(scoreItem);
		bRet = true;
	}while(0);

	return bRet;
}

void ControlLayer::menuPauseCallBack(CCObject* pSender)
{
	if(!CCDirector::sharedDirector()->isPaused())
	{  //����״̬�������ͣ
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));  
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));  
		CCDirector::sharedDirector()->pause();
	}
	else
	{  //��ͣ״̬���������
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));  
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));  
		CCDirector::sharedDirector()->resume();
	}
}

void ControlLayer::updateScore(int score)
{
	if (score >= 0 && score <= MAX_SCORE)
	{  
		CCString* strScore=CCString::createWithFormat("%d", score);
		scoreItem->setString(strScore->m_sString.c_str());
	}
}