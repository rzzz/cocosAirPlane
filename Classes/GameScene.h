/**�ļ�����GameScene.h
  *��������Ϸ������ͷ�ļ�
  *���ܣ������������Ϸ��Ҫ��
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