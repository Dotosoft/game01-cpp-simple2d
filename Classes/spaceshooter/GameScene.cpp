#include "spaceshooter/GameScene.h"
#include "spaceshooter/PauseScene.h"
#include "spaceshooter/GameOverScene.h"

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace spaceshooter;

Scene* GameScreen::createScene()
{
    // 'scene' is an autorelease object
    // auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = GameScreen::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto pauseItem =  MenuItemImage::create("GameScreen/Pause_Button.png",  "GameScreen/Pause_Button(Click).png",  CC_CALLBACK_1(GameScreen::GoToPauseScene, this));
    pauseItem->setPosition(Point(pauseItem->getContentSize().width -  (pauseItem->getContentSize().width / 4) + origin.x,  visibleSize.height - pauseItem->getContentSize().height +  (pauseItem->getContentSize().width / 4) + origin.y));
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    for (int i = 0; i < 2; i ++)
    {
    	backgroundSpriteArray[i] = Sprite::create("GameScreen/Game_Screen_Background.png");
    	backgroundSpriteArray[i]->setPosition(Point((visibleSize.width / 2) + origin.x, (-1 * visibleSize.height * i) + (visibleSize.height / 2) + origin.y));
    	this->addChild( backgroundSpriteArray[i], -2 );
    }

    playerSprite = Sprite::create("GameScreen/Space_Pod.png");
    auto body = PhysicsBody::createCircle( playerSprite->getContentSize().width / 2 );
    body->setContactTestBitmask( true );
    body->setDynamic( true );
    playerSprite->setPhysicsBody( body );

    playerSprite->setAnchorPoint( Vec2(0.5, 0.5) );
    playerSprite->setPosition( Point( (visibleSize.width / 2) + origin.x, pauseItem->getPosition().y - (pauseItem-> getContentSize().height / 2) - (playerSprite-> getContentSize().height / 2) + origin.y ) );
    this->addChild( playerSprite, 3 );

    this->scheduleUpdate();
    this->schedule(schedule_selector(GameScreen::spawnAsteroid), 1.0);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2 (GameScreen::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2 (GameScreen::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2 (GameScreen::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2 (GameScreen::onTouchCancelled, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    isTouching = false;
    touchPosition = 0;

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScreen::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    SimpleAudioEngine::getInstance()-> preloadEffect("spaceshooter/audio/Crash.wav");
    SimpleAudioEngine::getInstance()-> preloadEffect("spaceshooter/audio/ButtonClick.wav");

    return true;
}

void GameScreen::update(float dt)
{
	Size visibleSize = Director::getInstance()-> getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < 2; i ++) {
		if (backgroundSpriteArray[i]->getPosition().y >= visibleSize.height + (visibleSize.height / 2) -1)
		{
			backgroundSpriteArray[i]->setPosition ( Point((visibleSize.width / 2) + origin.x, (-1 * visibleSize.height) + (visibleSize.height / 2)));
		}
	}

	for (int i = 0; i < 2; i ++)
	{
		backgroundSpriteArray[i]->setPosition(Point(backgroundSpriteArray[i]->getPosition().x, backgroundSpriteArray[i]->getPosition().y + (0.75 * visibleSize.height * dt)));
	}

	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->setPosition(Point(asteroids[i]->getPosition().x, asteroids[i]->getPosition().y + (0.75 * visibleSize.height * dt)));
	    if (asteroids[i]->getPosition().y > visibleSize.height * 2)
	    {
	    	this->removeChild(asteroids[i]);
	    	asteroids.erase(asteroids.begin() + i);
	    }
	}

	// check if the screen is being touched
	if (true == isTouching) {
		float visibleWidthOrigin = visibleSize.width + origin.x;
		// check which half of the screen is being touched
		if (touchPosition < ( visibleSize.width / 2 ) + origin.x )
		{
			// move the space pod left
			playerSprite->setPositionX( playerSprite->getPosition().x - ( 0.50 * visibleWidthOrigin * dt ) );

			// check to prevent the space pod from going off  the screen (left side)
			if ( playerSprite->getPosition().x <= (0 + origin.x) + ( playerSprite->getContentSize().width / 2 ) )
			{
				playerSprite->setPositionX( origin.x + playerSprite->getContentSize().width / 2 );
			}
		}
		else {
			// move the space pod right
			playerSprite->setPositionX( playerSprite->getPosition().x + ( 0.50 * visibleWidthOrigin * dt ) );

			// check to prevent the space pod from going off the screen (right side)
			if (playerSprite->getPosition().x >= visibleWidthOrigin - ( playerSprite->getContentSize().width / 2 ) )
			{
				playerSprite->setPositionX( visibleWidthOrigin - ( playerSprite->getContentSize().width / 2 ) );
			}
		}

//		CCLOG("Position X: %d - %d", playerSprite->getPositionX(), touchPosition);
	}
}

void GameScreen::spawnAsteroid(float dt)
{
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	 Point origin = Director::getInstance()->     getVisibleOrigin();
	    int asteroidIndex = (arc4random() % 3) + 1;
	    __String* asteroidString = __String::createWithFormat("GameScreen/Asteroid_%i.png", asteroidIndex);
	    Sprite *tempAsteroid = Sprite::create(asteroidString->getCString());
	    int xRandomPosition = (arc4random() % (int) (visibleSize.width - (tempAsteroid->getContentSize().width / 2))) + (tempAsteroid->getContentSize().width / 2);
	    tempAsteroid->setPosition( Point(xRandomPosition + origin.x, -tempAsteroid->getContentSize().height + origin.y) );
	    asteroids.push_back( tempAsteroid );

	    // Set body physics for asteroids
	    auto body = PhysicsBody::createCircle(asteroids[asteroids.size() - 1]->getContentSize().width / 2);
		body->setContactTestBitmask(true);
		body->setDynamic(true);
		asteroids[asteroids.size() - 1]->setPhysicsBody(body);

	    this->addChild( asteroids[asteroids.size() - 1], -1 );
}

bool GameScreen::onContactBegin(PhysicsContact& contact) {
	SimpleAudioEngine::getInstance()-> playEffect("spaceshooter/audio/Crash.wav");
	GoToGameOverScene(this);
    return true;
}

void GameScreen::GoToPauseScene(cocos2d::Ref *pSender) {
	SimpleAudioEngine::getInstance()-> playEffect("spaceshooter/audio/ButtonClick.wav");

	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(scene);
}

void GameScreen::GoToGameOverScene(cocos2d::Ref *pSender) {
	SimpleAudioEngine::getInstance()-> playEffect("spaceshooter/audio/ButtonClick.wav");

	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene (TransitionZoomFlipY::create(3, scene));
}

bool GameScreen::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event* event)
{
	isTouching = true;
	touchPosition = touch->getLocation().x;
    return true;
}

void GameScreen::onTouchMoved(cocos2d::Touch *touch,cocos2d::Event* event)
{
	// not used for this game
}

void GameScreen::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event* event)
{
	isTouching = false;
}

void GameScreen::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event)
{
	onTouchEnded(touch, event);
}
