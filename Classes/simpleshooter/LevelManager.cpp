#include "simpleshooter/LevelManager.h"
#include "simpleshooter/Level.h"

using namespace simpleshooter;

LevelManager::LevelManager() {
	this->_levels = cocos2d::Vector<Level *>{100};
	this->_curLevelIdx = 0;

	Level *level1 = new Level(1, 2, cocos2d::Color4B(255, 255, 255, 255));
	Level *level2 = new Level(2, 1, cocos2d::Color4B(100, 150, 20, 255));

	this->_levels.pushBack(level1);
	this->_levels.pushBack(level2);
}

Level* LevelManager::getCurLevel() {
	if(this->_curLevelIdx >= _levels.size()) {
		return NULL;
	}
	return _levels.at(_curLevelIdx);
}

void LevelManager::nextLevel() {
	this->_curLevelIdx++;
}

void LevelManager::reset() {
	this->_curLevelIdx = 0;
}
