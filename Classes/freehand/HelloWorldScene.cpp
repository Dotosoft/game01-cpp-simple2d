#include "freehand/HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace freehand;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
AffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(Point::ZERO) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = AffineTransformMake( c, s, -s, c, x, y );

    return m_sTransform;
}

HelloWorld::HelloWorld()
{
//    setTouchEnabled( true );
//    setAccelerometerEnabled( true );

    Size s = Director::getInstance()->getWinSize();
    // init physics
    this->initPhysics();

    SpriteBatchNode *parent = SpriteBatchNode::create("freehand/blocks.png", 100);
    m_pSpriteTexture = parent->getTexture();

    addChild(parent, 0, kTagParentNode);

    //addNewSpriteAtPosition(ccp(s.width/2, s.height/2));

    Label *label = Label::createWithTTF( "Tap screen", "freehand/Marker Felt.ttf", 32 );
    addChild(label, 0);
    label->setColor(ccc3(0,0,255));
    label->setPosition(ccp( s.width/2, s.height-50));
    
    scheduleUpdate();
    
    target = RenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    target->retain();
    target->setPosition(ccp(s.width / 2, s.height / 2));
    this->addChild(target);
    
    brush = Sprite::create("freehand/largeBrush.png");
    brush->retain();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2( HelloWorld::onTouchBegan, this );
    listener->onTouchesMoved = CC_CALLBACK_2( HelloWorld::onTouchMoved, this );
    listener->onTouchesEnded = CC_CALLBACK_2( HelloWorld::onTouchEnded, this );
    getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}


void HelloWorld::addRectangleBetweenPointsToBody(b2Body *body, Point start, Point end)
{
    float distance = sqrt( pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    
    float sx=start.x;
    float sy=start.y;
    float ex=end.x;
    float ey=end.y;
    float dist_x=sx-ex;
    float dist_y=sy-ey;
    float angle= atan2(dist_y,dist_x);
    
    float px= (sx+ex)/2/PTM_RATIO - body->GetPosition().x;
    float py = (sy+ey)/2/PTM_RATIO - body->GetPosition().y;
    
    float width = abs(distance)/PTM_RATIO;
    float height =  brush->boundingBox().size.height/PTM_RATIO;
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2, height / 2, b2Vec2(px,py),angle);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 5;
    
    boxFixtureDef.filter.categoryBits = 2;
    
    body->CreateFixture(&boxFixtureDef);
}

Rect HelloWorld::getBodyRectangle(b2Body* body)
{
    Size s = Director::getInstance()->getWinSize();
    
    float minX2 = s.width;
    float maxX2 = 0;
    float minY2 = s.height;
    float maxY2 = 0;
    
    const b2Transform& xf = body->GetTransform();
    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
    {
        
        b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
        // int32 vertexCount = poly->m_vertexCount;
        int32 vertexCount = poly->m_count;
        b2Assert(vertexCount <= b2_maxPolygonVertices);
        
        for (int32 i = 0; i < vertexCount; ++i)
        {
            b2Vec2 vertex = b2Mul(xf, poly->m_vertices[i]);
            
            
            if(vertex.x < minX2)
            {
                minX2 = vertex.x;
            }
            
            if(vertex.x > maxX2)
            {
                maxX2 = vertex.x;
            }
            
            if(vertex.y < minY2)
            {
                minY2 = vertex.y;
            }
            
            if(vertex.y > maxY2)
            {
                maxY2 = vertex.y;
            }
        }
    }
    
    maxX2 *= PTM_RATIO;
    minX2 *= PTM_RATIO;
    maxY2 *= PTM_RATIO;
    minY2 *= PTM_RATIO;
    
    float width2 = maxX2 - minX2;
    float height2 = maxY2 - minY2;
    
    float remY2 = s.height - maxY2;
    
    return Rect(minX2, remY2, width2, height2);
}


HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
    
    //delete m_debugDraw;
}

void HelloWorld::initPhysics()
{

    Size s = Director::getInstance()->getWinSize();

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);

//     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
//     world->SetDebugDraw(m_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //m_debugDraw->SetFlags(flags);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom

    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

//void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
//{
//	_customCommand.init(_globalZOrder+10);
//	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this);
//	renderer->addCommand(&_customCommand);
//}
//
//void HelloWorld::onDraw()
//{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it
	//
//	Layer::draw();
//	glEnableVertexAttribArray( kCCVertexAttribFlag_Position );
//	kmGLPushMatrix();
//	world->DrawDebugData();
//	kmGLPopMatrix();
//}

void HelloWorld::addNewSpriteAtPosition(Point p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    Node* parent = getChildByTag(kTagParentNode);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    PhysicsSprite *sprite = new PhysicsSprite();
    sprite->initWithTexture(m_pSpriteTexture, Rect(32 * idx,32 * idy,32,32));
    sprite->autorelease();
    
    parent->addChild(sprite);
    
    sprite->setPosition( Vec2( p.x, p.y) );
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;    
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
}


void HelloWorld::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition( Vec2( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}


bool HelloWorld::onTouchBegan( const std::vector<Touch*>& touches, Event* evt )
{
    Size s = Director::getInstance()->getWinSize();

    for(Touch *touch : touches)
    {
        if(!touch) break;

		plataformPoints.clear();

        Point location = touch->getLocationInView();
        location = Director::getInstance()->convertToGL(location);

		plataformPoints.push_back(location);

        previousLocation = location;

        b2BodyDef myBodyDef;
        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(location.x/PTM_RATIO,location.y/PTM_RATIO);
        currentPlatformBody = world->CreateBody(&myBodyDef);
    }

	return true;
}

void HelloWorld::onTouchEnded( const std::vector<Touch*>& touches, Event* evt )
{
    //Add a new body/atlas sprite at the touched location
	for(Touch *touch : touches)
	{

        if(!touch)
            break;

        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
        myBodyDef.position.Set(currentPlatformBody->GetPosition().x, currentPlatformBody->GetPosition().y); //set the starting position
        b2Body* newBody = world->CreateBody(&myBodyDef);

        for(int i=0; i < plataformPoints.size()-1; i++)
        {
            Point start = plataformPoints[i];
            Point end = plataformPoints[i+1];
            addRectangleBetweenPointsToBody(newBody,start,end);

        }

        world->DestroyBody(currentPlatformBody);


        Size s = Director::getInstance()->getWinSize();

        Rect bodyRectangle = getBodyRectangle(newBody);

        Image *pImage = target->newCCImage();
        Texture2D *tex = Director::getInstance()->getTextureCache()->addUIImage(pImage,NULL);
        CC_SAFE_DELETE(pImage);

        //Sprite *sprite = Sprite::create(tex, bodyRectangle);

        Sprite *sprite = new Sprite();
        sprite->initWithTexture(tex, bodyRectangle);


        float anchorX = newBody->GetPosition().x * PTM_RATIO - bodyRectangle.origin.x;
        float anchorY = bodyRectangle.size.height - (s.height - bodyRectangle.origin.y - newBody->GetPosition().y * PTM_RATIO);

        sprite->setAnchorPoint( Vec2(anchorX / bodyRectangle.size.width,  anchorY / bodyRectangle.size.height) );
        newBody->SetUserData(sprite);
        addChild(sprite);

        removeChild(target,true);
        target->release();

        target = RenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
        target->retain();
        target->setPosition( Vec2(s.width / 2, s.height / 2) );

        this->addChild(target, 5);
    }
}

void HelloWorld::onTouchMoved( const std::vector<Touch*>& touches, Event* evt )
{
    Touch *touch = (Touch *) touches[0];
    Point start = touch->getLocationInView();
    start = Director::getInstance()->convertToGL(start);
    Point end = touch->getPreviousLocationInView();
    end = Director::getInstance()->convertToGL(end);

    target->begin();

    float distance = start.distance( end );

    for (int i = 0; i < distance; i++)
    {
        float difx = end.x - start.x;
        float dify = end.y - start.y;
        float delta = (float)i / distance;
        brush->setPosition( Vec2(start.x + (difx * delta), start.y + (dify * delta)) );

		//brush->setOpacity(0.1);
        brush->visit();
    }
    target->end();

    for(Touch *touch : touches)
    {
        if(!touch) break;

        Point location = touch->getLocationInView();

        location = CCDirector::getInstance()->convertToGL(location);

        float distance = sqrt( pow(location.x - previousLocation.x, 2) + pow(location.y - previousLocation.y, 2));

        if(distance > 15)
        {

            addRectangleBetweenPointsToBody(currentPlatformBody, previousLocation, location);
			plataformPoints.push_back(location);
            previousLocation = location;
        }
    }
}


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // add layer as a child to scene
    Layer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
