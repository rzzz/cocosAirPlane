//GameLayer.cpp
/**�ļ�����GameLayer.cpp
*��������Ϸ��������ʵ���ļ�
*/
#include "GameLayer.h"

bool GameLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		this->setKeypadEnabled(true);
		this->setTouchEnabled(true);		//��û�б�addChild�����Բ���������״̬������Ҳ�ǰ�����
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true); 
		this->scheduleUpdate();
		thisTimeScore = 0;

		background1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);

		background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background1->getContentSize().height -2 ));  //��2��ֹ���Ӵ����ߣ����ǿ��ܻ����ͼƬ���Ӳ�����
		this->addChild(background2);

		this->planeLayer = PlaneLayer::create();
		this->addChild(planeLayer);

		this->bulletLayer = BulletLayer::create();
		this->addChild(bulletLayer);
		this->bulletLayer->startShoot();

		this->enemyLayer = new EnemyLayer();
		this->enemyLayer->autorelease();
		enemyLayer->startEnemy(1);
		this->addChild(enemyLayer);

		this->controlLayer = ControlLayer::create();
		this->addChild(controlLayer);

		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f, kCCRepeatForever, 0);  //ʹ�ö�ʱ���ȣ�����ʹ��Ĭ�ϵ���

		bRet = true;
	}while(0);

	return bRet;
}

void GameLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if(background2->getPositionY() <= 0)
	{  //Ҫע����Ϊ����ͼ�߶���852������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô�����ֻ���ͣ�ٵĸо�  
		background1->setPositionY(0);
	}
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCPoint beginPoint = pTouch->locationInView();  //�˴���ȡUI����ϵ��Ҳ�ɻ��OpenGL����ϵ���汾��ͬ
	CCPoint beginPoint = pTouch->getLocationInView();
	beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint); //��ȡ��������

	CCRect planeRect = this->planeLayer->getChildByTag(PlaneLayer::AIRPLANE)->boundingBox();  //��ȡ�ɻ���ǰλ����״λ��
	planeRect.origin.x -= 15;  
	planeRect.origin.y -= 15;  
	planeRect.size.width += 30;  
	planeRect.size.height += 30;  //������΢�Ӵ�һ�㴥��λ�ã���Ϸʵ����Ҫ
	//if(CCRect::CCRectContainsPoint(planeRect,beginPoint) == true)  //��ײ��⣻�汾��ͬ
	if(planeRect.containsPoint(beginPoint) == true)
	{
		return true;
	}
	return false;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCPoint beginPoint = pTouch->locationInView();
	CCPoint beginPoint = pTouch->getLocationInView();
	beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);
	//CCPoint endPoint = pTouch->previousLocationInView();  //��ȡ������ǰһ��λ��
	CCPoint endPoint = pTouch->getPreviousLocationInView();
	endPoint = CCDirector::sharedDirector()->convertToGL(endPoint);
	CCPoint offSet = ccpSub(beginPoint, endPoint);  //��ȡoffset  
	CCPoint toPoint = ccpAdd(this->planeLayer->getChildByTag(PlaneLayer::AIRPLANE)->getPosition(), offSet); //��ȡ�����ƶ�λ��  
	this->planeLayer->moveTo(toPoint);  //�ƶ��ɻ�
}

void GameLayer::update(float dt)
{
	CCArray* bulletsToDelete = CCArray::create();  //����һ��CCArray�����Դ�Ŵ�ɾ�����ӵ���Ҳ���Ǵ�֡�б���⵽��ײ����
	bulletsToDelete->retain();  //�������retain��CCArray�ڲ�������autoRelease  
	CCObject *bt,*et;
	CCSprite* role = (CCSprite*)PlaneLayer::sharedPlane->getChildByTag(PlaneLayer::AIRPLANE);
	//�����ӵ�����Ӵ�ɾ���ӵ�����Ӵ�ɾ���л�
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		CCArray* enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		//�����л�
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			Enemy* enemy1 = (Enemy*)et;
			//if(CCRect::CCRectIntersectsRect(bullet->boundingBox(),enemy1->getBoundingBox()))
			if(bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{  //��ײ��⣬�����������Ƿ��ཻ��getBoundingBoxΪEnemy�ĳ�Ա����
				if(enemy1->getLife() > 1)
				{  //��������Ϊ2��������������loseLife()֮��Ϊ1����һ�λ�����ᱬը,���Ի�loseLife()��0������ֻ��Ϊ1ʱ�ű�ը
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if(enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1sToDelete->addObject(enemy1);
					this->thisTimeScore += 2;  //��ʱ���÷���Ϊ+2
					this->controlLayer->updateScore(thisTimeScore);
				}
				else
				{
				}
			}  //��ײ������
		}  //�����л�����

		//������ɾ���л�
		CCARRAY_FOREACH(enemy1sToDelete, et){
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();
	}  //���������ӵ�

	
	//������ɾ���ӵ�
	CCARRAY_FOREACH(bulletsToDelete, bt){
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete->release();
	//�����л��������������ײ����ɾ��������л�����������Ϸ
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et){
		Enemy* enemy1 = (Enemy*)et;
			//if(CCRect::CCRectIntersectsRect(role->boundingBox(),enemy1->getBoundingBox()))
			if(role->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if(enemy1->getLife()>1)
				{
					this->enemyLayer->enemy1Blowup(enemy1);
					this->enemyLayer->stopEnemy();
					this->bulletLayer->stopShoot();
					this->planeLayer->gameOver(thisTimeScore);
				}
			}  //��ײ������
	}
}

void GameLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();  //������Ϸ
}

void GameLayer::keyMenuClicked()
{
	//CCDirector::sharedDirector()  to do other things
}