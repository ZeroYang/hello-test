//
//  ScrollViewLayer.cpp
//  hello
//
//  Created by ZeroYang on 7/4/14.
//
//

#include "ScrollViewLayer.h"
#include "TableViewLayer.h"

#define pageCount (3)

ScrollViewLayer::ScrollViewLayer():
m_pScrollView(NULL)
{
}

ScrollViewLayer::~ScrollViewLayer()
{
}

bool ScrollViewLayer::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);
    
    //containLayer
    CCLayer *pContainLayer = CCLayer::create();
    //
    char temp[24]={0};
    for (int i = 1; i <= pageCount; i++) {
        memset(temp, 0, sizeof(temp));
        sprintf(temp, "help%d.png", i);
        
        CCSprite *pSprite = CCSprite::create(temp);
        pContainLayer->addChild(pSprite);
        pSprite->setPosition(CCPointMake(winSize.width * (i-0.5f), winSize.height/2));
    }
    
    m_nCurPage = 1;
    
    m_pScrollView = CCScrollView::create( CCSize(winSize.width, winSize.height), pContainLayer );
    this->addChild(m_pScrollView);
    m_pScrollView->setPosition(CCPointZero);
    m_pScrollView->setDelegate(this);
    m_pScrollView->setTouchEnabled(true);
    m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
    pContainLayer->setContentSize(CCSize(winSize.width * pageCount, winSize.height));
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PageControl.plist");
    for (int i = 1; i <= pageCount; i++) {
        CCSprite *pPoint = CCSprite::createWithSpriteFrameName("PageControlN.png");
        pPoint->setTag(i);
        pPoint->setPosition(ccp( (winSize.width - 3 * pPoint->getContentSize().width)/2 + pPoint->getContentSize().width * (i-1), 30));
        this->addChild(pPoint);
    }
    
    CCSprite *pPoint = (CCSprite *)this->getChildByTag(1);
    pPoint->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("PageControlS.png"));
    
    return true;
}

void ScrollViewLayer::scrollViewDidScroll(CCScrollView* view)
{
}

void ScrollViewLayer::scrollViewDidZoom(CCScrollView* view)
{
}

bool ScrollViewLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_touchPoint = pTouch->getLocation();
    return true;
}

void ScrollViewLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void ScrollViewLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint endPoint = pTouch->getLocation();
    float distance = endPoint.x - m_touchPoint.x;
    if(fabs(distance) > 50)
    {
        adjustScrollView(distance);
    }
}



void ScrollViewLayer::adjustScrollView(float offset)
{
    m_pScrollView->unscheduleAllSelectors();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSprite *pPoint = (CCSprite *)this->getChildByTag(m_nCurPage);
    pPoint->setDisplayFrame(pCache->spriteFrameByName("PageControlN.png"));
    if (offset<0)
    {
        m_nCurPage ++;
    }else
    {
        m_nCurPage --;
    }
    
    if (m_nCurPage <1)
    {
        m_nCurPage = 1;
    }
    
    if(m_nCurPage > 3)
    {
        removeFromParent();
    }
    else
    {
        pPoint = (CCSprite *)this->getChildByTag(m_nCurPage);
        pPoint->setDisplayFrame(pCache->spriteFrameByName("PageControlS.png"));
        CCPoint  adjustPos = ccp(origin.x - visibleSize.width * (m_nCurPage-1), 0);
        m_pScrollView->setContentOffset(adjustPos, true);
    }

}
