#ifndef _SIMPLESHOOTER_MONSTER_H_
#define _SIMPLESHOOTER_MONSTER_H_

#include "cocos2d.h"

namespace simpleshooter {

	class Monster : public cocos2d::Sprite
	{
		public:
			Monster(const std::string& filename, int p_hp, int p_minMoveDuration, int p_maxMoveDuration);
			int getHp() const { return hp; }
			void hit() { hp--; }
			int getMaxMoveDuration() const { return maxMoveDuration; }
			int getMinMoveDuration() const { return minMoveDuration; }

		private:
			int hp;
			int minMoveDuration;
			int maxMoveDuration;
	};

	class WeakAndFastMonster : public Monster
	{
		public:
			WeakAndFastMonster();
	};

	class StrongAndSlowMonster : public Monster
	{
		public:
			StrongAndSlowMonster();
	};

}

#endif // _SIMPLESHOOTER_MONSTER_H_
