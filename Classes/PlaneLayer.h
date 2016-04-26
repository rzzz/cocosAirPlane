/**文件名：PlaneLayer.h
  *描述：游戏飞机主角层头文件
  *功能：游戏飞机主角层，控制飞机的产生，飞行，爆炸效果
  */
#ifndef __R_PLANE_LAYER_H__
#define __R_PLANE_LAYER_H__
#include "cocos2d.h"

USING_NS_CC;

class PlaneLayer : public CCLayer
{
public:
	PlaneLayer();
	~PlaneLayer();
	static PlaneLayer* create();
	virtual bool init();

	void moveTo(CCPoint location);
	void blowup(int passScore);
	void removePlane();
	void gameOver(int passScore);
	void transGameOverScene();

	static PlaneLayer* sharedPlane;
	static const int AIRPLANE;
	bool isAlive;

private:
	int passScore;
};
#endif  //__R_PLANE_LAYER_H__