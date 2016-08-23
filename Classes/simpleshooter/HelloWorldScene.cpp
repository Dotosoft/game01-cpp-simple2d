#include "simpleshooter/HelloWorldScene.h"
#include "simpleshooter/GameOverScene.h"
#include "simpleshooter/LevelManager.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace simpleshooter;

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
    // if ( !LayerColor::initWithColor( Color4B( 255, 255, 255, 255 ) ) )
	if ( !LayerColor::initWithColor( LevelManager::getInstance().getCurLevel()->getBackgroundColor() ) )
    {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("simpleshooter/Sounds/background-music-aac.ogg" );

    this->_monsters = cocos2d::Vector<Monster *>{100};
    this->_projectiles = cocos2d::Vector<cocos2d::Node *>{100};

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _player = Sprite::create("simpleshooter/Art/player2.png");
    _player->setPosition( Vec2( _player->getContentSize().width / 2, winSize.height / 2 ) );
    this->addChild( _player );
    
    // this->schedule( schedule_selector( HelloWorld::gameLogic ), 1.0 );
    this->schedule( schedule_selector( HelloWorld::gameLogic ), LevelManager::getInstance().getCurLevel()->getSecsPerSpawn() );
    this->schedule( schedule_selector( HelloWorld::update ) );

    // this->setTouchEnabled(true);
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2( HelloWorld::onTouchBegan, this );
    touchListener->onTouchEnded = CC_CALLBACK_2( HelloWorld::onTouchEnded, this );
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( touchListener, this );

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::gameLogic(float dt)
{
	this->addMonster();
}

void HelloWorld::update(float dt)
{
	cocos2d::Vector<cocos2d::Node *> projectilesToDelete = cocos2d::Vector<cocos2d::Node *>{100};
	for(auto projectile : this->_projectiles) {
		bool monsterHit = false;
		cocos2d::Vector<Monster *> monstersToDelete = cocos2d::Vector<Monster *>{100};
		for(auto monster : this->_monsters) {
			if(monster->getBoundingBox().intersectsRect(projectile->getBoundingBox())) {

				monsterHit = true;
				monster->hit();
				if(monster->getHp() <= 0) {
					// Check if monster is killed until 30
					_monstersDestroyed++;
					if(_monstersDestroyed > 5) {
						Director::getInstance()->replaceScene(GameOver::createSceneWithWon(true));
					}
					monstersToDelete.pushBack(monster);
				}
				break;
			}
		}

		for(auto monster : monstersToDelete) {
			this->_monsters.eraseObject(monster);
			this->removeChild(monster, true);
		}

		// if(monstersToDelete.size() > 0) {
		if(monsterHit) {
			projectilesToDelete.pushBack(projectile);
			SimpleAudioEngine::getInstance()->playEffect("simpleshooter/Sounds/explosion.ogg");
		}
	}

	for(auto projectile : projectilesToDelete) {
		this->_projectiles.eraseObject(projectile);
		this->removeChild(projectile, true);
	}
}

void HelloWorld::addMonster()
{
	// Sprite *monster = Sprite::create("Art/monster.png");
	Monster *monster = NULL;
	if (arc4random() % 2 == 0) {
		monster = new WeakAndFastMonster();
	} else {
		monster = new StrongAndSlowMonster();
	}

	// Determine where to spawn the monster along the Y axis
	Size winSize = Director::getInstance()->getWinSize();
	int minY = monster->getContentSize().height / 2;
	int maxY = winSize.height - monster->getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (arc4random() % rangeY) + minY;

	// create the monster slightly off-screen along the right edge
	// and along a random position along the y axis as calculated above
	monster->setPosition( Vec2( winSize.width + monster->getContentSize().width / 2, actualY ) );
	this->addChild( monster );

	// Determine speed of the monster
	int minDuration = monster->getMinMoveDuration(); //2.0;
	int maxDuration = monster->getMaxMoveDuration(); //4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (arc4random() % rangeDuration) + minDuration;

	// Create the actions
	MoveTo *actionMove = MoveTo::create(actualDuration, Vec2( -monster->getContentSize().width / 2, actualY ) );
	auto actionMoveDone = CallFuncN::create([&](Node *node){
//		_monsters.eraseObject(node);
		node->removeFromParentAndCleanup(true);
	});
	// create a sequence with the actions and callbacks
	auto seq = Sequence::create( actionMove, actionMoveDone, NULL );
	monster->runAction( seq );

	monster->setTag(1);
	this->_monsters.pushBack(monster);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	// cocos2d::log("touch began");
	if (_nextProjectile) return false;

	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	// CCLOG("onTouchEnd");

	// Choose on of the touches to work with
	Vec2 location = touch->getLocation();

	// Set up initial localtion of projectile
	Size winSize = Director::getInstance()->getWinSize();
	_nextProjectile = Sprite::create("simpleshooter/Art/projectile2.png");
	_nextProjectile->setPosition( Vec2( 20, winSize.height / 2 ) );

	// Determine offset of location to projectile
	Vec2 offset = location - _nextProjectile->getPosition();

	// Bail out if you are shooting down or backwards
	if( offset.x <= 0 ) return;

	// Ok to add now - we've double checked position
	// this->addChild( projectile );

	int realX = winSize.width + ( _nextProjectile->getContentSize().width / 2 );
	float ratio = (float) offset.y / (float) offset.x;
	int realY = ( realX * ratio ) + _nextProjectile->getPosition().y;
	Vec2 realDest = Vec2(realX, realY);

	// Determine the length of how far you're shooting
	int offRealX = realX - _nextProjectile->getPosition().x;
	int offRealY = realY - _nextProjectile->getPosition().y;
	float length = sqrtf( ( offRealX*offRealX ) + ( offRealY * offRealY ) );
	float velocity = 480 / 1; // 480pixels/1sec
	float realMoveDuration = length / velocity;

	// Determine angle to face
	float angleRadians = atanf((float)offRealY / (float)offRealX);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = -1 * angleDegrees;
	// _player->setRotation(cocosAngle);
	float rotateDegreesPerSecond = 180 / 0.5; // Would take 0.5 seconds to rotate 180 degrees, or half a circle
	float degreesDiff = _player->getRotation() - cocosAngle;
	float rotateDuration = fabs(degreesDiff / rotateDegreesPerSecond);

	// Rotate player smoothly
	auto playerRotateAction = RotateTo::create(rotateDuration, cocosAngle);
	auto playerFinishAction = CallFuncN::create([&](Node *node){
		// OK to add now - rotation is finished
		this->addChild(_nextProjectile);
		_projectiles.pushBack(_nextProjectile);

		// Release
		// _nextProjectile->release();
		_nextProjectile = NULL;
	});
	auto playerSequence = Sequence::create( playerRotateAction, playerFinishAction, NULL ); // create a sequence with the actions and callbacks
	_player->runAction( playerSequence );

	// Move projectile to actual endpoint
	MoveTo *actionMove = MoveTo::create( realMoveDuration, realDest );
	auto actionMoveDone = CallFuncN::create([&](Node *node){
		this->_projectiles.eraseObject(node);
		node->removeFromParentAndCleanup(true);
	});
	auto projectileSequence = Sequence::create( actionMove, actionMoveDone, NULL ); // create a sequence with the actions and callbacks
	_nextProjectile->runAction( projectileSequence );

	_nextProjectile->setTag(2);
	// this->_projectiles.pushBack(projectile);
	SimpleAudioEngine::getInstance()->playEffect("simpleshooter/Sounds/pew-pew-lei.ogg");
}
