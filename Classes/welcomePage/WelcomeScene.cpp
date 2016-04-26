/**�ļ�����WelcomeScene.cpp
  *������Ӧ�ý����Ļ�ӭ���泡��ʵ���ļ�
  */
#include "WelcomeScene.h"
#include "WelcomeLayer.h"

bool WelcomeScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		WelcomeLayer* pWelcomeLayer = WelcomeLayer::create();
		CC_BREAK_IF(!pWelcomeLayer);
		this->addChild(pWelcomeLayer);

		bRet = true;
	}while(0);

	return bRet;
}