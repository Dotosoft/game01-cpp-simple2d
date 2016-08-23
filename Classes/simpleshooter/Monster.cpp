#include "simpleshooter/Monster.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace simpleshooter;

Monster::Monster(const std::string& filename, int p_hp, int p_minMoveDuration, int p_maxMoveDuration)
{
	if( initWithFile( filename ) ) {
		this->hp = p_hp;
		this->minMoveDuration = p_minMoveDuration;
		this->maxMoveDuration = p_maxMoveDuration;
	}
}

WeakAndFastMonster::WeakAndFastMonster() : Monster("simpleshooter/Art/monster.png", 1, 3, 5)
{
}

StrongAndSlowMonster::StrongAndSlowMonster() : Monster("simpleshooter/Art/monster2.png", 3, 6, 12)
{
}
