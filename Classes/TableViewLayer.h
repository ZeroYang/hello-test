//
//  TableViewLayer.h
//  hello
//
//  Created by ZeroYang on 7/4/14.
//
//

#ifndef __hello__TableViewLayer__
#define __hello__TableViewLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TableViewLayer : public CCLayer, public CCTableViewDelegate, public CCTableViewDataSource
{
public:
    
    TableViewLayer();
    ~TableViewLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static node()" method manually
    CREATE_FUNC(TableViewLayer);
    
public:
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    //DataList
    CCArray *m_pDataList;

};

#endif /* defined(__hello__TableViewLayer__) */
