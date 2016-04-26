#include "AppDelegate.h"
#include "AppMacros.h"
#include "welcomePage/WelcomeScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	int frameWidth = pEGLView->getFrameSize().width;
	int frameHeight = pEGLView->getFrameSize().height;
	pEGLView->setDesignResolutionSize(480, frameHeight*(480.0/frameWidth), kResolutionShowAll);
	//pEGLView->setDesignResolutionSize(320, 480, kResolutionNoBorder);

	//设置默认文件搜索目录；版本不同
	//CCFileUtils::sharedFileUtils()->setResourceDirectory("");
	//CCFileUtils::sharedFileUtils()->addSearchPath("");
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	CCScene *pWelcomeScene = WelcomeScene::create();

    // run
    pDirector->runWithScene(pWelcomeScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
