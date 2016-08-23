#include "spaceshooter/AppDelegate.h"
#include "spaceshooter/MainMenuScene.h"

USING_NS_CC;
using namespace spaceshooter;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
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
        glview = GLViewImpl::createWithRect("My Game", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("My Game");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto fileUtils = FileUtils::getInstance();
    auto screenSize = glview->getFrameSize();
    std::vector<std::string> resDirOrders;


	Size points = director->getWinSize();
	Size pixels = director->getWinSizeInPixels();
	Size design = glview->getDesignResolutionSize();
	ResolutionPolicy res = glview->getResolutionPolicy();
	Rect visibleRect = glview->getVisibleRect();
    CCLOG("Window Size:\n"
    		"\t%d x %d (points)\n"
    		"\t%d x %d (pixels)\n"
    		"\t%d x %d (design resolution)\n"
    		"Resolution Policy: %d\n"
    		"Visible Rect:\n"
    		"\torigin: %d x %d\n"
    		"\tsize: %d x %d\n",
		  (int)points.width, (int)points.height,
		  (int)pixels.width, (int)pixels.height,
		  (int)design.width, (int)design.height,
		  (int)res,
		  (int)visibleRect.origin.x, (int)visibleRect.origin.y,
		  (int)visibleRect.size.width, (int)visibleRect.size.height
	  );

    // check which assets the devices requires
    if( 2048 >= pixels.height ) // retina iPad
    {
    	resDirOrders.push_back("spaceshooter/ipadhd");
    	resDirOrders.push_back("spaceshooter/ipad");
    	resDirOrders.push_back("spaceshooter/iphonehd5");
    	resDirOrders.push_back("spaceshooter/iphonehd");
    	resDirOrders.push_back("spaceshooter/iphone");

    	glview->setDesignResolutionSize( 1536, 2048, ResolutionPolicy::NO_BORDER );
    }
    else if( 1136 >= pixels.height ) // retina iPhone (5 and 5S)
	{
		resDirOrders.push_back("spaceshooter/iphonehd5");
		resDirOrders.push_back("spaceshooter/iphonehd");
		resDirOrders.push_back("spaceshooter/iphone");

		glview->setDesignResolutionSize( 640, 1136, ResolutionPolicy::NO_BORDER );
	}
    else if( 1024 >= pixels.height ) // non retina iPad
    {
    	resDirOrders.push_back("spaceshooter/ipad");
    	resDirOrders.push_back("spaceshooter/iphonehd5");
    	resDirOrders.push_back("spaceshooter/iphonehd");
    	resDirOrders.push_back("spaceshooter/iphone");

    	glview->setDesignResolutionSize( 768, 1024, ResolutionPolicy::NO_BORDER );
    }
    else if( 960 >= pixels.height ) // retina iPhone (4 and 4S)
	{
		resDirOrders.push_back("spaceshooter/iphonehd");
		resDirOrders.push_back("spaceshooter/iphone");

		glview->setDesignResolutionSize( 640, 960, ResolutionPolicy::NO_BORDER );
	}
    else // non retina iPhone and Android devices
	{
    	if( 1080 < pixels.width ) // android devices that have a high resolution
    	{
    		resDirOrders.push_back("spaceshooter/iphonehd");
			resDirOrders.push_back("spaceshooter/iphone");
			glview->setDesignResolutionSize( 640, 960, ResolutionPolicy::NO_BORDER );
    	}
    	else // non retina iPhone and Android devices with lower resolutions
    	{
    		resDirOrders.push_back("spaceshooter/iphone");
			glview->setDesignResolutionSize( 320, 480, ResolutionPolicy::NO_BORDER );
    	}
	}

    fileUtils->setSearchPaths( resDirOrders );

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainMenu::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
