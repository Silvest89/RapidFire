#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "SplashScreen.h"


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1280, 720);
static cocos2d::Size smallResolutionSize = cocos2d::Size(960, 540);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1920, 1080);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2560, 1440);

typedef struct tagResource
{
	cocos2d::Size size; // The size that this resource is designed for
	char directory[100]; // The name of teh directory containing resources of this type
} Resource;

static Resource ultraResource = { Size(2048, 1536), "UD" };

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("RapidFire", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("RapidFire");
#endif
        director->setOpenGLView(glview);
    }
	std::vector<std::string> searchPaths;

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
	//glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	//director->setContentScaleFactor(1);
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
		searchPaths.push_back(ultraResource.directory);
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
		//director->setContentScaleFactor(MIN(designResolutionSize.height / largeResolutionSize.height, designResolutionSize.width / largeResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
		//director->setContentScaleFactor(MIN(designResolutionSize.height / mediumResolutionSize.height, designResolutionSize.width / mediumResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
		//director->setContentScaleFactor(MIN(designResolutionSize.height / smallResolutionSize.height, designResolutionSize.width / smallResolutionSize.width));
    }
	FileUtils::getInstance()->setSearchPaths(searchPaths);
    register_all_packages();

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto scene = SplashScreen::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
