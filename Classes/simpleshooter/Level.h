#ifndef _SIMPLESHOOTER_LEVEL_H_
#define _SIMPLESHOOTER_LEVEL_H_

#include "cocos2d.h"

namespace simpleshooter {

	class Level : public cocos2d::Ref
	{
		public:
			Level(int levelNum, float secsPerSpawn, cocos2d::Color4B backgroundColor);

			const cocos2d::Color4B& getBackgroundColor() const {
				return backgroundColor;
			}

			int getLevelNum() const {
				return levelNum;
			}

			float getSecsPerSpawn() const {
				return secsPerSpawn;
			}

		private:
			int levelNum;
			float secsPerSpawn;
			cocos2d::Color4B backgroundColor;
	};

}

#endif /* SIMPLESHOOTER_LEVEL_H_ */
