/**文件名：Enemy.cpp
  *描述：敌机父类实现文件
  */
#include "Enemy.h"

Enemy::Enemy()
{
	m_sprite = NULL;
	m_life = 0;
}

Enemy::~Enemy()
{

}

Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy;
	pRet -> autorelease();
	return pRet;
}

void Enemy::bindSprite(CCSprite* sprite, int life)
{
	m_sprite = sprite;
	m_life = life;
	this -> addChild(sprite);
}

CCSprite* Enemy::getSprite()
{
	return m_sprite;
}

int Enemy::getLife()
{
	return m_life;
}

void Enemy::loseLife(int num)
{
	m_life -= num;
}

CCRect Enemy::getBoundingBox()
{
	CCRect rect = m_sprite -> boundingBox();
	CCPoint pos = this->convertToWorldSpace(rect.origin);
	CCRect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}