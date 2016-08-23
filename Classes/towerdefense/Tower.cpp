#include "towerdefense/Tower.h"
#include "towerdefense/Enemy.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace towerdefense;

Tower* Tower::nodeWithTheGame(HelloWorld *game, Vec2 location) {
	Tower* tower = new Tower();
	if( !tower->init() ) {
		return tower;
	}

	tower->theGame = game;
	tower->attackRange = 70;
	tower->damage = 10;
	tower->fireRate = 1;

	tower->mySprite = Sprite::create( "towerdefense/art/tower.png" );
	tower->mySprite->setScale( tower->theGame->getScaleX(), tower->theGame->getScaleY() );
	tower->mySprite->setPosition(location);
	tower->addChild( tower->mySprite );
	tower->theGame->addChild( tower );

	tower->scheduleUpdate();

	return tower;
}

void Tower::update(float dt) {
	if( this->chosenEnemy ) {
		Vec2 normalized = Vec2( this->chosenEnemy->getMySprite()->getPosition().x - mySprite->getPosition().x, this->chosenEnemy->getMySprite()->getPosition().y - mySprite->getPosition().y );
		normalized.normalize();
		mySprite->setRotation( CC_RADIANS_TO_DEGREES( atan2(normalized.y, -normalized.x) ) + 90 );

		if(!this->theGame->circle(this->mySprite->getPosition(), attackRange, this->chosenEnemy->getMySprite()->getPosition(), 1))
		{
			this->lostSightOfEnemy();
		}
	} else {
		for( Enemy *enemy : this->theGame->getEnemies() )
		{
			if( this->theGame->circle( this->mySprite->getPosition(), this->attackRange, enemy->getMySprite()->getPosition(), 1 ) )
			{
				this->chosenEnemyForAttack( enemy );
				break;
			}
		}
	}
}

void Tower::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder+10);
	_customCommand.func = CC_CALLBACK_0(Tower::onDraw, this);
	renderer->addCommand(&_customCommand);
}

void Tower::onDraw()
{
	cocos2d::DrawPrimitives::setDrawColor4B( 255, 255, 255, 255 );
	cocos2d::DrawPrimitives::drawCircle( mySprite->getPosition(), attackRange, 360, 30, false );
}


void Tower::attackEnemy() {
	this->schedule( schedule_selector(Tower::shootWeapon), fireRate );
}

void Tower::chosenEnemyForAttack(Enemy *enemy) {
	this->chosenEnemy = NULL;
	this->chosenEnemy = enemy;
	this->attackEnemy();
	enemy->getAttacked(this);
}

void Tower::shootWeapon(float ccTime) {
	Sprite *bullet = Sprite::create( "towerdefense/art/bullet.png" );
	this->theGame->addChild( bullet );
	bullet->setPosition( mySprite->getPosition() );


	bullet->runAction(
		Sequence::create(
			MoveTo::create( 0.1f, this->chosenEnemy->getMySprite()->getPosition() ),
			CallFunc::create([&](){
				this->damageEnemy();
			}),
			CallFuncN::create([&](Node *node){
				this->removeBullet((Sprite*) node );
			}), NULL
		)
	);
}

void Tower::removeBullet(Sprite *bullet) {
	bullet->removeFromParentAndCleanup(true);
}

void Tower::damageEnemy() {
	this->chosenEnemy->getDamaged( damage );
}

void Tower::targetKilled() {
	if( this->chosenEnemy ) {
		chosenEnemy = NULL;
	}

	this->unschedule( schedule_selector(Tower::shootWeapon) );
}

void Tower::lostSightOfEnemy() {
	this->chosenEnemy->getLoseSight( this );
	if( this->chosenEnemy ) {
		this->chosenEnemy = NULL;
	}

	this->unschedule( schedule_selector(Tower::shootWeapon) );
}
