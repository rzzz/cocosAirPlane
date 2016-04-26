//GameLayer.cpp
/**文件名：GameLayer.cpp
*描述：游戏主场景层实现文件
*/
#include "GameLayer.h"

bool GameLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		this->setKeypadEnabled(true);
		this->setTouchEnabled(true);		//还没有被addChild，所以不处于运行状态，设置也是白设置
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true); 
		this->scheduleUpdate();
		thisTimeScore = 0;

		background1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);

		background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background1->getContentSize().height -2 ));  //减2防止交接处黑线，但是可能会造成图片连接不美观
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

		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f, kCCRepeatForever, 0);  //使用定时调度，而不使用默认调度

		bRet = true;
	}while(0);

	return bRet;
}

void GameLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if(background2->getPositionY() <= 0)
	{  //要注意因为背景图高度是852，所以每次减去2最后可以到达0，假如背景高度是841，那么则会出现画面停顿的感觉  
		background1->setPositionY(0);
	}
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCPoint beginPoint = pTouch->locationInView();  //此处获取UI坐标系，也可获得OpenGL坐标系；版本不同
	CCPoint beginPoint = pTouch->getLocationInView();
	beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint); //获取触摸坐标

	CCRect planeRect = this->planeLayer->getChildByTag(PlaneLayer::AIRPLANE)->boundingBox();  //获取飞机当前位置形状位置
	planeRect.origin.x -= 15;  
	planeRect.origin.y -= 15;  
	planeRect.size.width += 30;  
	planeRect.size.height += 30;  //允许稍微加大一点触摸位置，游戏实际需要
	//if(CCRect::CCRectContainsPoint(planeRect,beginPoint) == true)  //碰撞检测；版本不同
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
	//CCPoint endPoint = pTouch->previousLocationInView();  //获取触摸的前一个位置
	CCPoint endPoint = pTouch->getPreviousLocationInView();
	endPoint = CCDirector::sharedDirector()->convertToGL(endPoint);
	CCPoint offSet = ccpSub(beginPoint, endPoint);  //获取offset  
	CCPoint toPoint = ccpAdd(this->planeLayer->getChildByTag(PlaneLayer::AIRPLANE)->getPosition(), offSet); //获取真正移动位置  
	this->planeLayer->moveTo(toPoint);  //移动飞机
}

void GameLayer::update(float dt)
{
	CCArray* bulletsToDelete = CCArray::create();  //创建一个CCArray，用以存放待删除的子弹，也就是此帧中被检测到碰撞的子
	bulletsToDelete->retain();  //必须调用retain，CCArray内部调用了autoRelease  
	CCObject *bt,*et;
	CCSprite* role = (CCSprite*)PlaneLayer::sharedPlane->getChildByTag(PlaneLayer::AIRPLANE);
	//遍历子弹，添加待删除子弹，添加待删除敌机
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		CCArray* enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		//遍历敌机
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1, et)
		{
			Enemy* enemy1 = (Enemy*)et;
			//if(CCRect::CCRectIntersectsRect(bullet->boundingBox(),enemy1->getBoundingBox()))
			if(bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{  //碰撞检测，即矩形区域是否相交，getBoundingBox为Enemy的成员函数
				if(enemy1->getLife() > 1)
				{  //生命最少为2才满足条件，当loseLife()之后为1，下一次击打则会爆炸,但仍会loseLife()至0，所以只在为1时才爆炸
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if(enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1sToDelete->addObject(enemy1);
					this->thisTimeScore += 2;  //暂时设置分数为+2
					this->controlLayer->updateScore(thisTimeScore);
				}
				else
				{
				}
			}  //碰撞检测结束
		}  //遍历敌机结束

		//遍历待删除敌机
		CCARRAY_FOREACH(enemy1sToDelete, et){
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();
	}  //结束遍历子弹

	
	//遍历待删除子弹
	CCARRAY_FOREACH(bulletsToDelete, bt){
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete->release();
	//遍历敌机，如果与主角碰撞，则删除主角与敌机，并结束游戏
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
			}  //碰撞检测结束
	}
}

void GameLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();  //结束游戏
}

void GameLayer::keyMenuClicked()
{
	//CCDirector::sharedDirector()  to do other things
}