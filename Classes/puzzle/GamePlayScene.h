#ifndef _PUZZLE_GAMEPLAY_SCENE_H_
#define _PUZZLE_GAMEPLAY_SCENE_H_

#include "cocos2d.h"
#include "puzzle/Piece.h"

namespace puzzle {

	class GamePlay : public cocos2d::LayerColor
	{
		private:
			Vector<Piece *> puzzlePieces;

		public:
			// there's no 'id' in cpp, so we recommend returning the class instance pointer
			static cocos2d::Scene* createScene();

			// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(GamePlay);
	};

}

#endif // _PUZZLE_GAMEPLAY_SCENE_H_
