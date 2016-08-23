#include "spaceshooter/MainMenuScene.h"
#include "spaceshooter/GameScene.h"

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace spaceshooter;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create ("MainMenuScreen/Background.png");
	backgroundSprite->setPosition(Point((visibleSize.width / 2) +  origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(backgroundSprite, -1);

    auto menuTitle =  MenuItemImage::create( "MainMenuScreen/Game_Title.png",  "MainMenuScreen/Game_Title.png" );
    auto playItem =  MenuItemImage::create( "MainMenuScreen/Play_Button.png",  "MainMenuScreen/Play_Button(Click).png",  CC_CALLBACK_1(MainMenu::GoToGameScene, this) );

    auto menu = Menu::create( menuTitle, playItem, NULL );
    menu->alignItemsVerticallyWithPadding( visibleSize.height / 4 );
    this->addChild( menu );

    SimpleAudioEngine::getInstance()-> preloadEffect("spaceshooter/audio/ButtonClick.wav");
    if (CocosDenshion::SimpleAudioEngine::getInstance()-> isBackgroundMusicPlaying() == false)
    {
    	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("spaceshooter/audio/Music.mp3");
    	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("spaceshooter/audio/Music.mp3", true);
    }

    Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create (CC_CALLBACK_2(MainMenu::onAcceleration, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MainMenu::GoToGameScene(Ref *pSender) {
	SimpleAudioEngine::getInstance()-> playEffect("spaceshooter/audio/ButtonClick.wav");
	auto scene = GameScreen::createScene();
	Director::getInstance()->replaceScene (TransitionFlipX::create(3, scene));
}

void MainMenu::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event) {
	CCLOG("x = %f", acc->x);
	CCLOG("y = %f", acc->y);
	CCLOG("z = %f", acc->z);
}
