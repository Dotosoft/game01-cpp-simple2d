#include "maskedsprite\MainMenuScene.h"

USING_NS_CC;
using namespace maskedsprite;

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

	// ask director for the window size
	Size size = Director::getInstance()->getWinSize();

	// create and initialize a Label
	auto label = Label::createWithTTF("HJMaskedSprite Demo", RESOURCES_FLAPPY_FONT_MARKER, 55);

	// position the label on the center of the screen
	label->setPosition( Vec2(size.width / 2, size.height - label->getBoundingBox().size.height));

	// add the label as a child to this Layer
	this->addChild(label);

	//
	// Masked Sprite with image overlaying text
	//
	demoSprite = MaskedSprite::createWithFile("maskedsprite/stickman.png", "maskedsprite/Default-Landscape~ipad.png");
	demoSprite->setScale((size.width / 4) / demoSprite->getBoundingBox().size.width);
	demoSprite->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
	this->addChild(demoSprite);

	overlaySprite = Sprite::create("maskedsprite/Default-Landscape~ipad.png");
	overlaySprite->setScale((size.width / 6) / overlaySprite->getBoundingBox().size.width);
	overlaySprite->setPosition(Vec2(size.width - size.width / 4 - overlaySprite->getBoundingBox().size.height, size.height / 2 - overlaySprite->getBoundingBox().size.height));
	this->addChild(overlaySprite);

	normalSprite = Sprite::create("maskedsprite/stickman.png");
	normalSprite->setScale((size.width / 4) / normalSprite->getBoundingBox().size.width);
	normalSprite->setPosition( Vec2(size.width - size.width / 4 + overlaySprite->getBoundingBox().size.height / 2, size.height / 2 - overlaySprite->getBoundingBox().size.height));
	this->addChild(normalSprite);

	// Default font size will be 28 points.
	MenuItemFont::setFontSize(28);

	// Overlaying Text Menu Item using blocks
	auto itemOverText = MenuItemFont::create("Image overlaying Image", [&](Ref * sender) {
		this->removeChild(demoSprite, true);
		demoSprite = MaskedSprite::createWithFile("maskedsprite/stickman.png", "maskedsprite/Default-Landscape~ipad.png");
		demoSprite->setScale((size.width / 4) / demoSprite->getBoundingBox().size.width);
		demoSprite->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
		this->addChild(demoSprite);
	});

	// Overlaying Text with Sprite Menu Item using blocks
	auto itemOverTextWithSprite = MenuItemFont::create("Image overlaying text", [&](Ref * sender) {
		this->removeChild(demoSprite, true);
		auto demoLabel = Label::createWithTTF("Demo Text Overlay", RESOURCES_FLAPPY_FONT_ARIAL, 40);
		// demoSprite = MaskedSprite::initWithSprite(demoLabel, "Default-Landscape~ipad.png");
		demoSprite->setScale((size.width / 4) / demoSprite->getBoundingBox().size.width);
		demoSprite->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
		this->addChild(demoSprite);
	});

	// Overlaying Image Menu Item using blocks
	auto itemOverImage = MenuItemFont::create("Sprite overlaying Text", [&](Ref * sender) {
		this->removeChild(demoSprite, true);
		auto demoLabel = Label::createWithTTF("Demo Text Overlay", RESOURCES_FLAPPY_FONT_ARIAL, 50);
		auto tempSprite = Sprite::create("maskedsprite/Icon@2x.png");
		// demoSprite = MaskedSprite::createWithSprite((Sprite *)demoLabel->getChildByTag(0), tempSprite);
		demoSprite->setScale((size.width / 4) / demoSprite->getBoundingBox().size.width);
		demoSprite->setPosition(Vec2(size.width - size.width / 4, size.height / 2));
		this->addChild(demoSprite);
	});

	auto menu = Menu::create(itemOverText, itemOverTextWithSprite, itemOverImage, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Vec2(size.width / 4, size.height / 2 - 50));

	// Add the menu to the layer
	this->addChild(menu);


    return true;
}