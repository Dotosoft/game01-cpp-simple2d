#include "squishybox2d\MainMenuScene.h"
#include "squishybox2d\MyNode.h"

USING_NS_CC;
using namespace squishybox2d;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size screenSize = Director::getInstance()->getWinSize();
	CCLOG("Screen width %0.2f screen height %0.2f", screenSize.width, screenSize.height);

	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	// This will speed up the physics simulation
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	// world = new b2World(gravity, doSleep);
	this->world = new b2World(gravity);

	/*
	world->SetContinuousPhysics(true);

	// Debug Draw functions
	// m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	// world->SetDebugDraw(m_debugDraw);

	// uint32 flags = 0;
	// flags += b2DebugDraw::e_shapeBit;
	// flags += b2DebugDraw::e_jointBit;
	// flags += b2DebugDraw::e_aabbBit;
	// flags += b2DebugDraw::e_pairBit;
	// flags += b2DebugDraw::e_centerOfMassBit;
	// m_debugDraw->SetFlags(flags);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// bottom
	// groundBox.SetAsEdge(b2Vec2(0, 0), b2Vec2(screenSize.width / PTM_RATIO, 0));
	// groundBody->CreateFixture(&groundBox, 0);

	// top
	// groundBox.SetAsEdge(b2Vec2(0, screenSize.height / PTM_RATIO), b2Vec2(screenSize.width / PTM_RATIO, screenSize.height / PTM_RATIO));
	// groundBody->CreateFixture(&groundBox, 0);

	// left
	// groundBox.SetAsEdge(b2Vec2(0, screenSize.height / PTM_RATIO), b2Vec2(0, 0));
	// groundBody->CreateFixture(&groundBox, 0);

	// right
	// groundBox.SetAsEdge(b2Vec2(screenSize.width / PTM_RATIO, screenSize.height / PTM_RATIO), b2Vec2(screenSize.width / PTM_RATIO, 0));
	// groundBody->CreateFixture(&groundBox, 0);

	groundBox.SetAsBox(0, 0, b2Vec2(0, 0), 0);
	groundBody->CreateFixture(&groundBox, 0);
	*/

	// MyNode is the squishy physics
	auto node = new MyNode();
	node->setPosition(Vec2(screenSize.width/2, screenSize.height/2));
	node->createPhysicsObject(world);
	this->addChild(node);

    return true;
}