#include "towerdefense/Enemy.h"
#include "towerdefense/Tower.h"
#include "towerdefense/Waypoint.h"
#include "SimpleAudioEngine.h"

#define HEALTH_BAR_WIDTH 20
#define HEALTH_BAR_ORIGIN -10

using namespace CocosDenshion;
using namespace towerdefense;

Enemy* Enemy::nodeWithTheGame(HelloWorld *_game) {
	Enemy *enemy = new Enemy();
	if(!enemy->init()) {
		return enemy;
	}

	enemy->attackedBy = Vector<Tower *>( 5 );

	enemy->theGame = _game;
	enemy->maxHp = 40;
	enemy->currentHp = enemy->maxHp;
	enemy->active = false;
	enemy->walkingSpeed = 0.5f;
	enemy->mySprite = Sprite::create("towerdefense/art/enemy.png");
	enemy->mySprite->setScale( _game->getScaleX(), _game->getScaleY() );
	enemy->addChild( enemy->mySprite );

	Waypoint *waypoint = (Waypoint *) enemy->theGame->getWaypoints().at( enemy->theGame->getWaypoints().size() - 1 );
	enemy->destinationWaypoint = waypoint->getNextWaypoint();

	Vec2 pos = waypoint->getMyPosition();
	enemy->myPosition = pos;
	enemy->mySprite->setPosition( pos );
	enemy->theGame->addChild(enemy);
	enemy->scheduleUpdate();

	return enemy;
}

void Enemy::doActivate(float ccTime) {
	this->active = true;
}

void Enemy::update(float ccTime) {
	if(!this->active) return;
	if(this->theGame->circle(this->myPosition, 1, this->destinationWaypoint->getMyPosition(), 1))
	{
		if(this->destinationWaypoint->getNextWaypoint())
		{
			this->destinationWaypoint = this->destinationWaypoint->getNextWaypoint();
		}
		else {
			// Reached the end of the road. Damage the player
			this->theGame->getHpDamage();
			this->getRemoved();
		}
	}
	Vec2 targetPoint = this->destinationWaypoint->getMyPosition();
	float movementSpeed = this->walkingSpeed;

	Vec2 normalized = Vec2(targetPoint.x - this->myPosition.x, targetPoint.y - this->myPosition.y);
	normalized.normalize();
	this->mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, -normalized.x)));
	this->myPosition = Vec2(this->myPosition.x + normalized.x * movementSpeed, this->myPosition.y + normalized.y * movementSpeed);
	this->mySprite->setPosition(this->myPosition);
}

void Enemy::getRemoved() {
	for( Tower *attacker : attackedBy )
	{
		attacker->targetKilled();
	}

	// Node::removeChild(this, true);
	this->theGame->removeChild( this, true );
	this->theGame->getEnemies().eraseObject( this );

	//Notify the game that we killed an enemy so we can check if we can send another wave
	this->theGame->enemyGotKilled();
}

void Enemy::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder+10);
	_customCommand.func = CC_CALLBACK_0(Enemy::onDraw, this);
	renderer->addCommand(&_customCommand);
}

// Draw Enemy Health Bar
void Enemy::onDraw()
{
	cocos2d::DrawPrimitives::drawSolidRect (
		Vec2(myPosition.x + HEALTH_BAR_ORIGIN, myPosition.y + 16),
		Vec2(myPosition.x + HEALTH_BAR_ORIGIN + HEALTH_BAR_WIDTH, myPosition.y + 14),
		Color4F(1.0, 0, 0, 1.0)
	);

	cocos2d::DrawPrimitives::drawSolidRect (
		Vec2(myPosition.x + HEALTH_BAR_ORIGIN, myPosition.y + 16),
		Vec2(myPosition.x + HEALTH_BAR_ORIGIN + ( float ) ( this->currentHp * HEALTH_BAR_WIDTH ) / this->maxHp, this->myPosition.y + 14 ),
		Color4F(0, 1.0, 0, 1.0)
	);
}

void Enemy::getAttacked(Tower *attacker)
{
	this->attackedBy.pushBack( attacker );
}

void Enemy::getLoseSight(Tower *attacker)
{
	this->attackedBy.eraseObject( attacker );
}

void Enemy::getDamaged(int damage)
{
	SimpleAudioEngine::getInstance()->playEffect( "towerdefense/sounds/laser_shoot.wav" );

	this->currentHp -= damage;
	if( currentHp <= 0)
	{
		this->theGame->awardGold( 200 );
		this->getRemoved();
	}
}
