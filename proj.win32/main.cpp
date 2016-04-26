#include "main.h"
#include "../Classes/AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);//该宏用于通知编译器不用检测变量是否使用
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();	
	eglView->setViewName("Airplane");
    eglView->setFrameSize(320, 480);
    //eglView->setFrameZoomFactor(0.4f);

    return CCApplication::sharedApplication()->run();
}
