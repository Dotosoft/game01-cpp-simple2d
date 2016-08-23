#include "gallery/HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace gallery;

Scene* HelloWorld::createScene()
{
	 auto scene = Scene::create();
	 auto layer = HelloWorld::create();
	 layer->currImageIndex=1;
	 scene->addChild(layer);
	 return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    // if ( !LayerColor::initWithColor( Color4B( 255, 255, 255, 255 ) ) )
	if ( !Layer::init() )
    {
        return false;
    }

	HelloWorld::displayImage(this);

    return true;
}

void HelloWorld::displayImage(Layer *myLayer) {
	if(this->currImageIndex<1)this->currImageIndex=1;
	Sprite *currImage = Sprite::create( myImages[this->currImageIndex -1] );
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	currImage->setPosition(
		Vec2(
			visibleSize.width/2 + origin.x,
			visibleSize.height/2 + origin.y
		)
	);

	float aspectRatio=currImage->getContentSize().width/currImage->getContentSize().height;

	float newwidth=aspectRatio*visibleSize.height;
	float xR=newwidth/currImage->getContentSize().width ;
	float yR=visibleSize.height/currImage->getContentSize().height;
	currImage->setScaleX(xR);    currImage->setScaleY(yR);
	myLayer->addChild(currImage);
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [&](Touch* touch, Event* event){
		pointStartPos=touch->getLocation();
		return true;
	};
	listener1->onTouchMoved = [&](Touch* touch, Event* event){    };
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
    	 pointEndPos=touch->getLocation();
    	 bool is_left;
    	 unsigned int i_index=this->currImageIndex;
    	 if(pointEndPos.x - pointStartPos.x >0) {
    		 is_left=true;
    		 i_index++;
    	 }
    	 else {
    		 is_left=false;
    		 i_index--;
    	 }
    	 if(i_index==0) i_index=myImages.size();
    	 if(i_index>myImages.size()) i_index=1;
    	 this->currImageIndex=i_index;
    	 SimpleAudioEngine::getInstance()->playEffect("gallery/Hit.mp3");
    	 Director::getInstance()->setDepthTest(true);
    	 //Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f, HelloWorld::scene(i_index), is _left));
    	 if(is_left)Director::getInstance()->replaceScene( TransitionSlideInL::create( 1, HelloWorld::scene(i_index) ) );
    	 else Director::getInstance()->replaceScene( TransitionSlideInR::create( 1, HelloWorld::scene(i_index) ) );
	 };
	 auto dispatcher = Director::getInstance()->getEventDispatcher();
	 dispatcher->addEventListenerWithSceneGraphPriority(listener1, this );
 }

Scene* HelloWorld::scene(unsigned int i_index) {
	 auto scene = Scene::create();
	 auto layer = HelloWorld::create();
	 layer->currImageIndex=i_index;

	 HelloWorld::displayImage(layer);
	 scene->addChild(layer);
	 return scene;
}

std::vector<std::string> myImages = {
	"gallery/image001.png",
	"gallery/image002.png",
	"gallery/image003.png"
};
