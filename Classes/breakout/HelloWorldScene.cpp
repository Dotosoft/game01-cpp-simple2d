#include "breakout/HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace breakout;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();
    // auto glview = Director::getInstance()->getOpenGLView();
    // auto winSize = glview->getFrameSize();
    // CCLOG("frameSize: %d %d", frameSize.height, frameSize.width);

    // Create a world
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    _world = new b2World(gravity);

    // Create edges around the entire screen
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,0);
    _groundBody = _world->CreateBody(&groundBodyDef);

    b2EdgeShape groundBox;
    b2FixtureDef groundBoxDef;
    groundBoxDef.shape = &groundBox;

    groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PTM_RATIO, 0));
    _bottomFixture = _groundBody->CreateFixture(&groundBoxDef);

    groundBox.Set(b2Vec2(0,0), b2Vec2(0, winSize.height/PTM_RATIO));
    _groundBody->CreateFixture(&groundBoxDef);

    groundBox.Set(b2Vec2(125, winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO));
    _groundBody->CreateFixture(&groundBoxDef);

    groundBox.Set(b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO, 0));
    _groundBody->CreateFixture(&groundBoxDef);

    // Create sprite and add it to the layer
    Sprite *ball = Sprite::create("breakout/ball.png");
    ball->setPosition( Vec2(100, 100) );
    ball->setTag(1);
    this->addChild(ball);

    // Create ball body
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(100/PTM_RATIO, 100 / PTM_RATIO);
    ballBodyDef.userData = ball;
    b2Body * ballBody = _world->CreateBody(&ballBodyDef);

    // Create circle shape
    b2CircleShape circle;
    circle.m_radius = 26.0/PTM_RATIO;

    // Create shape definition and add to body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 1.0f;
    _ballFixture = ballBody->CreateFixture(&ballShapeDef);

    b2Vec2 force = b2Vec2(10, 10);
    ballBody->ApplyLinearImpulse(force, ballBodyDef.position, true);

    this->schedule(schedule_selector(HelloWorld::tick));

    return true;
}

void HelloWorld::tick(float dt)  {
    _world->Step(dt, 10, 10);
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            Sprite *sprite = (Sprite *) b->GetUserData();
            sprite->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
            sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
