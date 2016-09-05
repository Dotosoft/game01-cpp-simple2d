#include "clipsprite\MainMenuScene.h"

USING_NS_CC;
using namespace clipsprite;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size winSize = Director::getInstance()->getWinSize();

	auto stencil = DrawNode::create();
	stencil->drawSolidCircle(Vec2(0.0f, 0.0f), 50.0f, 0.0f, 32.0f, Color4F::GREEN);

	// create the clipping node and set the stencil 
	auto clipper = ClippingNode::create();
	clipper->setStencil(stencil);
	clipper->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	// create the sprite, which should be clipped
	auto sprite = Sprite::create("maskedsprite/Default.png");

	// add the sprite to the clipping node, so it can be clipped
	clipper->addChild(sprite);

	// add the clipping node to the main node
	addChild(clipper);

    return true;
}