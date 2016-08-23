#include "towerdefense/IntroScene.h"
#include "towerdefense/HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace towerdefense;

Scene* Intro::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Intro::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Intro::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor( Color4B( 255, 255, 255, 255 ) ) )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();

    Sprite *background= Sprite::create( "towerdefense/art/Default.png" );
	background->setRotation( 90 );
	background->setPosition( Vec2( winSize.width / 2, winSize.height / 2 ) );

	// add the label as a child to this Layer
	this->addChild( background );

    return true;
}


void Intro::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Intro::onEnter()
{
	LayerColor::onEnter();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
}
