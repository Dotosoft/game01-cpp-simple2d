#include "simpleshooter/Level.h"

using namespace simpleshooter;

Level::Level(int levelNum, float secsPerSpawn, cocos2d::Color4B backgroundColor)
{
	this->levelNum = levelNum;
	this->secsPerSpawn = secsPerSpawn;
	this->backgroundColor = backgroundColor;
}
