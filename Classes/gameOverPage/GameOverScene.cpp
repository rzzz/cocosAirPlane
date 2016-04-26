/**文件名：GameOverScene.cpp
  *描述：游戏结束场景实现文件
  */
#include "GameOverScene.h"
#include "GameOverLayer.h"
GameOverScene::GameOverScene()
{
}

GameOverScene::GameOverScene(int passScore)
{
	GameOverLayer* pGameOverLayer = GameOverLayer::create(passScore);
	this->addChild(pGameOverLayer);
}

GameOverScene::~GameOverScene()
{
}