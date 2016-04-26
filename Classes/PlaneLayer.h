/**�ļ�����PlaneLayer.h
  *��������Ϸ�ɻ����ǲ�ͷ�ļ�
  *���ܣ���Ϸ�ɻ����ǲ㣬���Ʒɻ��Ĳ��������У���ըЧ��
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