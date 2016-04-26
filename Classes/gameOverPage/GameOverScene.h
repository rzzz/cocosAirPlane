/**文件名：GameOverScene.h
  *描述：游戏结束场景头文件
  *功能：游戏结束场景，创建并添加游戏结束层
  */
#ifndef __R_GAMEOVER_SCENE_H__
#define __R_GAMEOVER_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public CCScene
{
public:
	GameOverScene();
	GameOverScene(int passScore);
	~GameOverScene();
};
#endif  //__R_GAMEOVER_SCENE_H__