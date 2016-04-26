/**文件名：GameScene.cpp
*描述：游戏主场景实现文件
*/
#include "GameScene.h"
/*
GameScene::GameScene()
{
	//_gameLayer = NULL;
}

GameScene::~GameScene()
{
	//_gameLayer = NULL;
}
*/
bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		GameLayer* _gameLayer = GameLayer::create();
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer);

		bRet = true;
	}while(0);

	return bRet;
}