/**�ļ�����GameOverScene.h
  *��������Ϸ��������ͷ�ļ�
  *���ܣ���Ϸ���������������������Ϸ������
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