#include "towerdefense/HelloWorldScene.h"
#include "towerdefense/Tower.h"
#include "towerdefense/Waypoint.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace towerdefense;

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
    if ( !LayerColor::initWithColor( Color4B( 255, 255, 255, 255 ) ) )
    {
        return false;
    }
    
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches( true );
	touchListener->onTouchBegan = CC_CALLBACK_2( HelloWorld::onTouchBegan, this );
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( touchListener, this );

    // 1 - initialize
    // this->setTouchEnabled(true);
    Size winSize = Director::getInstance()->getWinSize();

	// 2 - set background
    Sprite *background = Sprite::create("towerdefense/art/bg.png");
    // background->setPosition( Vec2( winSize.width / 2, winSize.height / 2) );

    Rect s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    this->_scaleY = s_visibleRect.size.height / background->getContentSize().height;
    this->_scaleX = s_visibleRect.size.width / background->getContentSize().width;
    if(this->_scaleX > this->_scaleY){
    	background->setScale( this->_scaleX );
    }else{
    	background->setScale( this->_scaleY );
    }
    background->setPosition( Vec2( s_visibleRect.origin.x + s_visibleRect.size.width/2, s_visibleRect.origin.y + s_visibleRect.size.height / 2 ) );
    this->addChild( background );

	// 3 - load tower positions
    this->_towerBases = cocos2d::Vector<cocos2d::Sprite *>(10);
    this->_towers = cocos2d::Vector<Tower *>(10);
    this->loadTowerPositions();

	// 4 - add waypoints
    this->_waypoints = cocos2d::Vector<Waypoint *>(10);
    this->addWaypoints();

    // 5 - create wave label
    // this->ui_wave_lbl = Label::createWithBMFont(__String::createWithFormat( "WAVE: %d", wave)->getCString(), "towerdefense/fonts/font_red_14.fnt", TextHAlignment::LEFT, 14, Vec2::ZERO );
    this->ui_wave_lbl = Label::createWithBMFont( "towerdefense/fonts/font_red_14.fnt", __String::createWithFormat( "WAVE: %d", wave)->getCString() );
    this->ui_wave_lbl->setScale( this->_scaleX, this->_scaleY );
	this->ui_wave_lbl->setPosition( Vec2( 400, winSize.height - 15 ) );
	this->ui_wave_lbl->setAnchorPoint( Vec2( 0, 0.5f ) );
	this->addChild( this->ui_wave_lbl, 10 );

	// 6 - add enemies
    this->_enemies = cocos2d::Vector<Enemy *>(10);
    this->loadWave();

	// 7 - player lives
    this->playerHp = 5;
    this->ui_hp_lbl = Label::createWithBMFont( "towerdefense/fonts/font_red_14.fnt", __String::createWithFormat( "HP: %d", this->playerHp )->getCString() );
    this->ui_hp_lbl->setScale( this->_scaleX, this->_scaleY );
    this->ui_hp_lbl->setPosition( Vec2( 35, winSize.height - 15 ) );
    this->ui_hp_lbl->setAnchorPoint( Vec2( 0, 0.5f ) );
    this->addChild( this->ui_hp_lbl, 10 );

	// 8 - gold
    this->playerGold = 1000;
    this->ui_gold_lbl = Label::createWithBMFont( "towerdefense/fonts/font_red_14.fnt", __String::createWithFormat( "GOLD: %d", this->playerGold )->getCString() );
    this->ui_gold_lbl->setScale( this->_scaleX, this->_scaleY );
	this->ui_gold_lbl->setPosition( Vec2( 135, winSize.height - 15 ) );
	this->ui_gold_lbl->setAnchorPoint( Vec2( 0, 0.5f ) );
	this->addChild( this->ui_gold_lbl, 10 );

	// 9 - sound
	SimpleAudioEngine::getInstance()->playBackgroundMusic( "towerdefense/sounds/8bitDungeonLevel.mp3", true );

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::loadTowerPositions() {

	// auto spritecache = SpriteFrameCache::getInstance();
	// spritecache->addSpriteFramesWithFile("towerdefense/art/TowersPosition.plist");
	// auto mysprite = Sprite::createWithSpriteFrameName("mysprite.png");

	std::string plistPath = FileUtils::getInstance()->fullPathForFilename("towerdefense/data/TowersPosition.plist");
	// cocos2d::log( "%s", plistPath.c_str() );
	ValueMap data = FileUtils::getInstance()->getValueMapFromFile(plistPath);
	auto towerPositions = data.at("towersPositionData").asValueVector();
	for (int i = 0; i<towerPositions.size(); i++) {
	    ValueMap towerPos = (towerPositions[i]).asValueMap();
		Sprite *towerBase = Sprite::create("towerdefense/art/open_spot.png");
		towerBase->setScale( this->_scaleX, this->_scaleY );
		towerBase->setPosition( Vec2( towerPos["x"].asInt(), towerPos["y"].asInt() ) );
		this->addChild(towerBase);
		this->_towerBases.pushBack(towerBase);
	}
}

void HelloWorld::addWaypoints() {
	Waypoint *waypoint1 = Waypoint::nodeWithTheGame( this, Vec2(420, 35), NULL );
	this->_waypoints.pushBack( waypoint1 );

	Waypoint *waypoint2 = Waypoint::nodeWithTheGame( this, Vec2(35, 35), waypoint1 );
	this->_waypoints.pushBack( waypoint2 );

	Waypoint *waypoint3 = Waypoint::nodeWithTheGame( this, Vec2(35, 130), waypoint2 );
	this->_waypoints.pushBack( waypoint3 );

	Waypoint *waypoint4 = Waypoint::nodeWithTheGame( this, Vec2(445,130), waypoint3 );
	this->_waypoints.pushBack( waypoint4 );

	Waypoint *waypoint5 = Waypoint::nodeWithTheGame( this, Vec2(445,220), waypoint4 );
	this->_waypoints.pushBack( waypoint5 );

	Waypoint *waypoint6 = Waypoint::nodeWithTheGame( this, Vec2(-40,220), waypoint5 );
	this->_waypoints.pushBack( waypoint6 );

}

bool HelloWorld::canBuyTower() {
	if( this->playerGold - kTOWER_COST >= 0 )
	{
		return true;
	}

	return false;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location = touch->getLocation();
	Director::getInstance()->convertToGL(location);
	for(Sprite *tb : this->_towerBases)
	{
		if(tb->getBoundingBox().containsPoint(location)
			&& this->canBuyTower()
			&& !tb->getUserData()) {

			SimpleAudioEngine::getInstance()->playEffect( "towerdefense/sounds/tower_place.wav" );

			this->playerGold -= kTOWER_COST;
			this->ui_gold_lbl->setString( __String::createWithFormat("GOLD: %d", this->playerGold )->getCString() );

			//We will spend our gold later.
			Tower *tower = Tower::nodeWithTheGame(this, tb->getPosition());
			this->_towers.pushBack(tower);
			tb->setUserData(tower);
		}
	}

	return true;
}


bool HelloWorld::circle( Vec2 circlePoint, float radius, Vec2 circlePointTwo, float radiusTwo ) {
	float xdif = circlePoint.x - circlePointTwo.x;
	float ydif = circlePoint.y - circlePointTwo.y;

	float distance = sqrt(xdif * xdif + ydif * ydif);

	if(distance <= radius + radiusTwo)
	{
		return true;
	}

	return false;
}

bool HelloWorld::loadWave() {
	std::string plistPath = FileUtils::getInstance()->fullPathForFilename("towerdefense/data/Waves.plist");
	ValueMap data = FileUtils::getInstance()->getValueMapFromFile( plistPath );
	ValueVector waveData = data.at("wavesData").asValueVector();
	if(wave >= waveData.size())
	{
		return  false;
	}

	ValueVector currentWaveData = waveData.at(wave).asValueVector();
	for (int i = 0; i<currentWaveData.size(); i++)
	{
		ValueMap enemyData = ( currentWaveData[i] ).asValueMap();
		Enemy *enemy = Enemy::nodeWithTheGame(this);
		this->_enemies.pushBack( enemy );
		enemy->schedule( schedule_selector( Enemy::doActivate ), enemyData["spawnTime"].asFloat() );
	}

	this->wave++;
	this->ui_wave_lbl->setString( __String::createWithFormat( "WAVE: %d", wave)->getCString() );

	return  true;
}

void HelloWorld::enemyGotKilled() {
	// if there is no more enemies
	if(this->_enemies.size() <= 0)
	{
		if(!this->loadWave())
		{
			CCLOG("You win!");
			Director::getInstance()->replaceScene(TransitionSplitCols::create(1, HelloWorld::createScene()));
		}
	}
}

void HelloWorld::getHpDamage() {
	SimpleAudioEngine::getInstance()->playEffect( "towerdefense/sounds/life_lose.wav" );

	this->playerHp--;
	this->ui_hp_lbl->setString( __String::createWithFormat( "HP: %d", this->playerHp )->getCString() );
	if( this->playerHp <= 0 ) {
		this->doGameOver();
	}
}

void HelloWorld::doGameOver()
{
	if(!gameEnded) {
		gameEnded = true;
		Director::getInstance()->replaceScene( TransitionRotoZoom::create( 1, HelloWorld::createScene() ) );
	}
}

void HelloWorld::ccFillPoly(Vec2 *poli, int points, bool closePolygon) {

}

void HelloWorld::awardGold(int gold)
{
	this->playerGold += gold;
	this->ui_gold_lbl->setString( __String::createWithFormat("GOLD: %d", this->playerGold )->getCString() );
}
