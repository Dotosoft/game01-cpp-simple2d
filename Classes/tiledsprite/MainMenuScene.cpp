#include "tiledsprite\MainMenuScene.h"

USING_NS_CC;
using namespace tiledsprite;

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

	auto sourceSprite = Sprite::create(RESOURCES_TILED_IMAGE_BRICK);
	sourceSprite->setAnchorPoint(Vec2::ZERO);
	sourceSprite->setPosition(Vec2(20, 100));
	this->addChild(sourceSprite);

	auto croppedSprite = new TiledSprite(sourceSprite, 16, 16);
	croppedSprite->setAnchorPoint(Vec2::ZERO);
	croppedSprite->setPosition(Vec2(60, 100));
	this->addChild(croppedSprite);

	auto skinnySprite = new TiledSprite(sourceSprite, 10, 50);
	skinnySprite->setAnchorPoint(Vec2::ZERO);
	skinnySprite->setPosition(Vec2(84, 100));
	this->addChild(skinnySprite);

	auto longSprite = new TiledSprite(sourceSprite, 100, 20);
	longSprite->setAnchorPoint(Vec2::ZERO);
	longSprite->setPosition(Vec2(102, 100));
	this->addChild(longSprite);

	auto bigSprite = new TiledSprite(sourceSprite, 160, 120);
	bigSprite->setAnchorPoint(Vec2::ZERO);
	bigSprite->setPosition(Vec2(210, 100));
	this->addChild(bigSprite);

    return true;
}

void MainMenuScene::GoToGameScene( cocos2d::Ref *sender )
{
}