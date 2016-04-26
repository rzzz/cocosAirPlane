/**文件名：GameScene.h
  *描述：游戏主场景头文件
  *功能：创建并添加游戏主要层
  */
#ifndef __R_GAME_SCENE_H__
#define __R_GAME_SCENE_H__
#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public CCScene
{
public:
	//GameScene();
	//~GameScene();

	CREATE_FUNC(GameScene);
	virtual bool init();

	//GameLayer* _gameLayer;
};
#endif //__R_GAME_SCENE_H__