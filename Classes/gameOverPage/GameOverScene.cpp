/**�ļ�����GameOverScene.cpp
  *��������Ϸ��������ʵ���ļ�
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