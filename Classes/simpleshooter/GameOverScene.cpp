#include "simpleshooter/GameOverScene.h"
#include "simpleshooter/HelloWorldScene.h"
#include "simpleshooter/LevelManager.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace simpleshooter;

Scene* GameOver::createSceneWithWon(bool win)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();
    layer->setWon(win);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor( Color4B( 255, 255, 255, 255 ) ) )
    {
        return false;
    }

    return true;
}

void GameOver::setWon(bool won)
{
    __String *message;
    if(won) {
    	LevelManager::getInstance().nextLevel();
    	Level *curLevel = LevelManager::getInstance().getCurLevel();
    	if(curLevel) {
    		message = __String::createWithFormat( "Get ready for level%d!", curLevel->getLevelNum() );
    	} else {
    		message = __String::create( "You Won!" );
    		LevelManager::getInstance().reset();
    	}
    } else {
    	message = __String::create ( "You Lose:[" );
    	LevelManager::getInstance().reset();
    }

    Size winSize = Director::getInstance()->getWinSize();
    cocos2d::Label *label = Label::createWithTTF( message->getCString(), "simpleshooter/fonts/arial.ttf", 32 );
    label->setColor(Color3B::BLACK);
    label->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(label);

    // Create the actions
	auto *actionDelay = DelayTime::create(3);
	auto *actionDone = CallFuncN::create([&](Node *node){
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	// create a sequence with the actions and callbacks
	auto seq = Sequence::create( actionDelay, actionDone, NULL );
	this->runAction( seq );
}
