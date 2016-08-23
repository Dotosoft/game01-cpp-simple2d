#ifndef _SIMPLESHOOTER_LEVEL_MANAGER_H_
#define _SIMPLESHOOTER_LEVEL_MANAGER_H_

#include "simpleshooter/Level.h"
#include "cocos2d.h"

namespace simpleshooter {

	class LevelManager
	{
		public:
			// Singleton Method
			static LevelManager& getInstance() {
				static LevelManager instance;
				return instance;
			}
			LevelManager(LevelManager const&)	= delete;
			void operator=(LevelManager const&)	= delete;

			// Level Manager Method
			Level *getCurLevel();
			void nextLevel();
			void reset();
		private:
			LevelManager();
			// LevelManager(LevelManager const&);		// Don't Implement
			// void operator=(LevelManager const&);	// Don't implement

			cocos2d::Vector<Level *> _levels;
			int _curLevelIdx;
	};

}

#endif /* _SIMPLESHOOTER_LEVEL_MANAGER_H_ */
