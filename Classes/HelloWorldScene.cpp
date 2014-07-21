#include "HelloWorldScene.h"
#include "TableViewLayer.h"
#include "ScrollViewLayer.h"

USING_NS_CC;

#include "cocos-ext.h"

USING_NS_CC_EXT;

#include "Lightning.h"
#include "SimpleAudioEngine.h"
#include "layer_lightningBolt.h"

#include "LightLayer.h"

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    CCScale9Sprite *bgSprite = CCScale9Sprite::create("HelloWorld.png");
    bgSprite->setContentSize(CCSize(200, 40));
    CCEditBox *pEditbox = CCEditBox::create(CCSize(200, 40), bgSprite);
    pEditbox->setPosition(CCPointMake(origin.x + visibleSize.width/2, origin.y + visibleSize.height - pEditbox->getContentSize().height));
    this->addChild(pEditbox);
    pEditbox->setTag(100);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    auto layer = CCLayerColor::create(ccc4(0, 0, 0, 255));
	addChild(layer, -10);
    
	//
//	auto btnSprite = CCSprite::create("btn.png");
//	btnSprite->setPosition(CCPoint(200, 250));
//	btnSprite->setAnchorPoint(CCPoint(0, 0));
//	this->addChild(btnSprite, 1);
//    
//	auto starSprite = CCSprite::create("star1.png");
//	starSprite->setScale(0.4f);
//	this->addChild(starSprite, 10);
//    
//	auto _emitter = particleInit();
//	starSprite->setPosition(CCPoint(btnSprite->getPosition().x + btnSprite->getContentSize().height / 2 - 4, btnSprite->getPosition().y));
//    
//    
//	_emitter->setPosition(CCPoint(btnSprite->getPosition().x + btnSprite->getContentSize().height / 2 - 6, btnSprite->getPosition().y + 3));
//    
//	float X = btnSprite->getContentSize().height / 2;
//	auto path = MyPathFun(X+10, btnSprite->getContentSize().height, btnSprite->getContentSize().width - X * 2 /*+ starSprite->getContentSize().width*/);
//    
//	starSprite->runAction(path);
//	_emitter->runAction(MyPathFun(X+10, btnSprite->getContentSize().height, btnSprite->getContentSize().width - X * 2 /*+ starSprite->getContentSize().width*/));
    
    
    Lightning* l = Lightning::create(ccp(160,640), ccp(200, 20));
    l->setVisible(false);
    this->addChild(l, 1, 999);
    
    //this->schedule(schedule_selector(HelloWorld::strikeLight), 2.0f,kCCRepeatForever,3.0f);
    //strikeLight(0);
    
    
    auto close = CCSprite::create("CloseNormal.png");
    addChild(close);
    close->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    CCActionInterval * orbitcamera = CCOrbitCamera::create(30, 10, 0, 45, 180, 90, 0);
    pSprite->runAction(orbitcamera);
    
    
    CCPointArray * array = CCPointArray::create(20);
    array->addControlPoint(ccp(0,0));
    array->addControlPoint(ccp(210,0));
    array->addControlPoint(ccp(210,240));
    array->addControlPoint(ccp(0,160));
    array->addControlPoint(ccp(0,0));
    
    CCActionInterval  * CardinalSplineTo=CCCardinalSplineTo::create(3, array, 0);
    
    CCRepeatForever *repeat = CCRepeatForever::create(CardinalSplineTo);
    close->runAction(repeat);
    
    
//	//°´Å¥1
//	auto btnSprite1 = CCSprite::create("btn1.png");
//	btnSprite1->setPosition(CCPoint(600, 250));
//	btnSprite1->setAnchorPoint(CCPoint(0, 0));
//	this->addChild(btnSprite1, 10);
//    
//	auto path1 = MyPathFun(75, btnSprite1->getContentSize().height, 80);
//	auto _emitter1 = particleInit();
//	auto starSprite1 = CCSprite::create("star1.png");
//	starSprite1->setScale(0.4f);
//	this->addChild(starSprite1, 10);
//    
//	starSprite1->setPosition(CCPoint(btnSprite1->getPosition().x + btnSprite1->getContentSize().height / 2 - 4, btnSprite1->getPosition().y));
//	_emitter1->setPosition(CCPoint(btnSprite1->getPosition().x + btnSprite1->getContentSize().height / 2 - 5, btnSprite1->getPosition().y + 3));
//    
//	starSprite1->runAction(path1);
//	_emitter1->runAction(path1);
//    
//    
//	//°´Å¥2£¨¾ØÐÎ£©
//	auto btnSprite2 = CCSprite::create("btn0.png");
//	btnSprite2->setPosition(CCPoint(350, 150));
//	btnSprite2->setAnchorPoint(CCPoint(0, 0));
//	this->addChild(btnSprite2, 10);
//    
//	auto path2 = MyPathFun(0, btnSprite2->getContentSize().height, btnSprite2->getContentSize().width );
//	auto _emitter2 = particleInit();
//	auto starSprite2 = CCSprite::create("star1.png");
//	starSprite2->setScale(0.4f);
//	this->addChild(starSprite2, 10);
//    
//	starSprite2->setPosition(CCPoint(btnSprite2->getPosition().x  - 2, btnSprite2->getPosition().y));
//	_emitter2->setPosition(CCPoint(btnSprite2->getPosition().x  - 2, btnSprite2->getPosition().y + 3));
//    
//	starSprite2->runAction(path2);
//	_emitter2->runAction(path2);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//    TableViewLayer *layer = TableViewLayer::create();
//    getParent()->addChild(layer);
    
//    CCEditBox *editBox = (CCEditBox*)this->getChildByTag(100);
//    CCLOG("%s",editBox->getText());
//    auto *layer = ScrollViewLayer::create();
//    getParent()->addChild(layer);
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
    
    
    Clayer_lightningBolt *layer = new Clayer_lightningBolt();
    layer->autorelease();
    layer->init();
    getParent()->addChild(layer);
    
//    LightLayer *llayer = LightLayer::create();
//    getParent()->addChild(llayer);
//    llayer->setTag(1000);
//    
//
//    this->schedule(schedule_selector(HelloWorld::strikeLight), 2.0f,kCCRepeatForever,3.0f);
    
    
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    
//    CCPoint start=CCPoint(0,winSize.height);
//    CCPoint end=CCPoint(winSize.width,0);
//    
//    ClightningBoltNode *m_lbNode=new ClightningBoltNode();
//    m_lbNode->autorelease();
//    m_lbNode->init(start, end);
//    addChild(m_lbNode);
//    lightningBolt::CflashAction*flash=lightningBolt::CflashAction::create(5,0.7);//-1 for repeat forever
//    m_lbNode->runAction(flash);
    
    
    //CCBezierBy&CCBezierTo
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    ccBezierConfig bezier;
//    bezier.controlPoint_1 = CCPoint(10,winSize.height/2);
//    bezier.controlPoint_2 = CCPoint(winSize.width/2,winSize.height/3);
//    bezier.endPosition = CCPoint(0, winSize.width);
//    
//    CCBezierBy *ac1= CCBezierBy::create(2.0f, bezier);
//    
//    CCBezierTo *ac2 = CCBezierTo::create(2.0f, bezier);
//    
//    auto sprtite = CCSprite::create("CloseSelected.png");
//    sprtite->runAction(ac2);
//    this->addChild(sprtite);
    
}

CCParticleSystem* HelloWorld::particleInit(){
	auto _emitter = new CCParticleSystemQuad();
	_emitter->initWithTotalParticles(50);
	addChild(_emitter, 10);
    auto sp = CCSprite::create("point.png");

	_emitter->setTexture(sp->getTexture());
	_emitter->setAnchorPoint(CCPoint(0, 0));
	// duration
	_emitter->setDuration(kParticleDurationInfinity);
    
	// radius mode
	_emitter->setEmitterMode(kCCParticleModeRadius);
    
	// radius mode: start and end radius in pixels
	_emitter->setStartRadius(4);
	_emitter->setStartRadiusVar(1);
	_emitter->setEndRadius(kCCParticleStartRadiusEqualToEndRadius);
	_emitter->setEndRadiusVar(0);
    
	// radius mode: degrees per second
	_emitter->setRotatePerSecond(100);
	_emitter->setRotatePerSecondVar(0);
    
	// angle
	_emitter->setAngle(90);
	_emitter->setAngleVar(0);
    
	// emitter position
	auto size = CCDirector::sharedDirector()->getWinSize();
	_emitter->setPosVar(CCPointZero);
    
	// life of particles
	_emitter->setLife(0.5);
	_emitter->setLifeVar(0);
    
	// spin of particles
	_emitter->setStartSpin(0);
	_emitter->setStartSpinVar(0);
	_emitter->setEndSpin(0);
	_emitter->setEndSpinVar(0);
    
	// color of particles
	ccColor4F startColor = ccc4f(0.0f, 0.8f, 0.9f, 1.0f);
	_emitter->setStartColor(startColor);
    
	ccColor4F startColorVar = ccc4f(0, 0, 0, 1.0f);
	_emitter->setStartColorVar(startColorVar);
    
	ccColor4F endColor = ccc4f(1.0f, 1.0f, 1.0f, 0.1f);
	_emitter->setEndColor(endColor);
    
	ccColor4F endColorVar = ccc4f(0, 0, 0, 0.1f);
	_emitter->setEndColorVar(endColorVar);
	ccColor4F setStartColor = ccc4f(50, 50, 50, 50);
	ccColor4F setEndColor = ccc4f(0, 0, 0, 0);
	// size, in pixels
	_emitter->setStartSize(20);
	_emitter->setStartSizeVar(1);
	_emitter->setEndSize(0);
    
	// emits per second
	_emitter->setEmissionRate(_emitter->getTotalParticles() / _emitter->getLife());
    
	// additive
	_emitter->setBlendAdditive(false);
    
	return _emitter;
}

CCRepeatForever* HelloWorld::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = CCPoint(-controlX, 0);
	bezier1.controlPoint_2 = CCPoint(-controlX, controlY);
	bezier1.endPosition = CCPoint(0, controlY);
	auto bezierBy1 = CCBezierBy::create(0.8f, bezier1);
    
	auto move1 = CCMoveBy::create(0.8f, CCPoint(w, 0));
    
	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = CCPoint(controlX, 0);
	bezier2.controlPoint_2 = CCPoint(controlX, -controlY);
	bezier2.endPosition = CCPoint(0, -controlY);
	auto bezierBy2 = CCBezierBy::create(0.8f, bezier2);
	auto move2 = CCMoveBy::create(0.8f, CCPoint(-w, 0));
	auto path = CCRepeatForever::create(CCSequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}

void HelloWorld::draw()
{

//    
//    drawLighting(ccp(100, 900), ccp(400, 100), 500, 10);
//    drawLighting(ccp(100+2, 900), ccp(400, 100), 500, 10);
}

void HelloWorld::drawLighting(const CCPoint &beginPoint, const CCPoint &endPoint, int displaceCount, int endCount) {
    if (displaceCount < endCount) {  //递归终点，displaceCount每次都会衰减为一半
        ccDrawLine(beginPoint, endPoint);  // 画线
    } else {
        // 计算中间点
        CCPoint mid = ccp((beginPoint.x + endPoint.x) / 2, (beginPoint.y + endPoint.y) / 2);
        
        // 随机移动上下，左右移动这个点，注意displace这里控制‘震动’的幅度。
        mid.x += (CCRANDOM_0_1() - 0.5) * displaceCount;
        mid.y += (CCRANDOM_0_1() - 0.5) * displaceCount;
        
        // 递归上面的算法
        drawLighting(beginPoint, mid, displaceCount / 2, endCount);
        drawLighting(endPoint, mid, displaceCount / 2, endCount);
    }
}

void HelloWorld::strikeLight(float dt){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("thunderSound.wav", false);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    LightLayer *layer = (LightLayer*)getParent()->getChildByTag(1000);
    layer->light(ccp(winSize.width/2, winSize.height/2));
    
//	Lightning *l = (Lightning *)this->getChildByTag(999);
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//	srand(time(NULL));
//	//random position
//	l->setBeginPoint(ccp(20 + CCRANDOM_0_1() * winSize.width/2, winSize.height));
//	l->setEndPoint(ccp(20 + CCRANDOM_0_1() * winSize.width, 10));
//	//l->setStrikePoint3(ccp(20 + CCRANDOM_0_1() * winSize.width, 10));
//    
//	//random color
//	l->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
//    
//	//random style
//	l->setDisplacement(100 + CCRANDOM_0_1() * 400);
//	l->setMinDisplacement(4 + CCRANDOM_0_1() * 4);
//	l->setLighteningWidth(2.0f);
//	l->setSplit(true);
//    
//	//call strike
//	l->strikeRandom();
}
