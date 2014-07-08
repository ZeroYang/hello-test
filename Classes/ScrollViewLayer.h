//
//  ScrollViewLayer.h
//  hello
//
//  Created by ZeroYang on 7/4/14.
//
//

#ifndef __hello__ScrollViewLayer__
#define __hello__ScrollViewLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScrollViewLayer : public CCLayer, public CCScrollViewDelegate
{
public:
    
    ScrollViewLayer();
    ~ScrollViewLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(ScrollViewLayer);
    
public:
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    
    virtual void scrollViewDidZoom(CCScrollView* view);

    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    
private:
    
    void adjustScrollView(float offset);
    
    CCScrollView *m_pScrollView;
    
    CCPoint m_touchPoint;
    int m_nCurPage;
    
};

#endif /* defined(__hello__ScrollViewLayer__) */
