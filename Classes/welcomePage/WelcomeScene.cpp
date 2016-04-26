/**文件名：WelcomeScene.cpp
  *描述：应用进入后的欢迎界面场景实现文件
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