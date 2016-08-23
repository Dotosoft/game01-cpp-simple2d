#include "puzzle/GamePlayScene.h"

USING_NS_CC;
using namespace puzzle;

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Add Background shape
    Sprite * background = Sprite::create("puzzle/background.png");
    background->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(background);
    
    // Position of pieces
    Vec2 positionPieceTopLeft     = Vec2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vec2 positionPieceTopRight    = Vec2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vec2 positionPieceBottomLeft  = Vec2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);
    
    Vec2 positionPieceBottomRight = Vec2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);
    
    Vec2 positionsArray[4];
    positionsArray[0] = positionPieceTopLeft;
    positionsArray[1] = positionPieceTopRight;
    positionsArray[2] = positionPieceBottomLeft;
    positionsArray[3] = positionPieceBottomRight;
    
    
    this->puzzlePieces = cocos2d::Vector<Piece *>{4};
    
    for (int i = 0; i < 4; i++)
    {
        // Add piece
    	__String *imagePath = __String::createWithFormat("puzzle/piece_0%d.png", i);
        std::cout<<imagePath->getCString();
        Piece * piece = Piece::create( imagePath->getCString() );
        piece->setTargetPosition(positionsArray[i]);
        this->puzzlePieces.pushBack(piece);
        this->addChild(piece);
    }
    
    return true;
}
