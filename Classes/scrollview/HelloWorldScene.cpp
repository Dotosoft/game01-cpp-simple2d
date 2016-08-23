#include "scrollview/HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace scrollview;

#define LISTVIEW_HEIGHT 500;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();

    //add scroll view
//    Size scollFrameSize = Size(visibleSize.width, visibleSize.height);
//    auto scrollView = cocos2d::ui::ScrollView::create();
//    scrollView->setContentSize(scollFrameSize);
//    scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
//    scrollView->setBackGroundColor(Color3B(200, 200, 200));
//    CCLOG("Visible Size %d, %d", visibleSize.width, visibleSize.height);
//    scrollView->setPosition(Point(135, 0));
//    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
//    scrollView->setBounceEnabled(true);
//    scrollView->setTouchEnabled(true);
//    auto containerSize = Size(scollFrameSize.width, scollFrameSize.height*2);
//    scrollView->setInnerContainerSize(containerSize);
//
//    auto button1 = cocos2d::ui::Button::create();
//    button1->setColor(Color3B::RED);
//    button1->setTouchEnabled(true);
//    button1->setContentSize(Size(100, 100));
//    button1->setPosition(Point(25, 50));
//    scrollView->addChild(button1);

    /*auto button1 = ui::Button::create();
    button1->setTouchEnabled(true);
    button1->ignoreContentAdaptWithSize(false);
    button1->setContentSize(Size(100, 100));
    button1->loadTextures("pic1.png", "pic2.png");
    button1->setPosition(Point(containerSize.width / 8, containerSize.height / 2));
    scrollView->addChild(button1);*/

//    auto button2 = cocos2d::ui::Button::create();
//    button2->setColor(Color3B::BLUE);
//    button1->setContentSize(Size(100, 100));
//    button2->setTouchEnabled(true);
//    button2->setPosition(Point(50, 50));
//    scrollView->addChild(button2);
//
//    this->addChild(scrollView);



    auto greenBox = Sprite::create("puzzle/piece_00.png");

    auto listView = cocos2d::ui::ListView::create();
    cocos2d::ui::Layout* layout = cocos2d::ui::Layout::create();
    layout->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B::WHITE);
    layout->setContentSize(cocos2d::Size(960, 50));
    layout->addChild(greenBox);
    listView->pushBackCustomItem(layout);
    listView->setItemsMargin(10);
    listView->setGravity(cocos2d::ui::ListViewGravity::CENTER_VERTICAL);
    listView->setContentSize(Size(960, 500));
    listView->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    listView->setBackGroundColor(Color3B::WHITE);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);
    this->addChild(listView);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
