//
//  TableViewLayer.cpp
//  hello
//
//  Created by ZeroYang on 7/4/14.
//
//

#include "TableViewLayer.h"

#define COUNT (20)

TableViewLayer::TableViewLayer():
m_pDataList(NULL)
{
}

TableViewLayer::~TableViewLayer()
{
    m_pDataList->release();
}

bool TableViewLayer::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_pDataList = CCArray::create();
    m_pDataList->retain();
    
    for (int i = 0; i < COUNT; i++) {
        
        CCString *pString = CCString::createWithFormat("tableCell_%d", i);
        m_pDataList->addObject(pString);
    }
    
    CCTableView *pTableView = CCTableView::create(this, CCSizeMake(640, 960));
    pTableView->setDirection(kCCScrollViewDirectionVertical);
    pTableView->setPosition(CCPoint(0, 0));
    pTableView->setDelegate(this);
    pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(pTableView);
    pTableView->reloadData();
    
    
    return true;
}

void TableViewLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize TableViewLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(640, 120);
}

CCTableViewCell* TableViewLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *pString = (CCString*)m_pDataList->objectAtIndex(idx);
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCSprite *pSprite = CCSprite::create("listitem.png");
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
        CCLabelTTF *pLabel = CCLabelTTF::create(pString->getCString(), "Arial", 20.0);
        pLabel->setPosition(CCPointZero);
        pLabel->setAnchorPoint(CCPointZero);
        pLabel->setTag(123);
        pLabel->setColor(ccc3(0, 0, 0));
        pCell->addChild(pLabel);
    }
    else
    {
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
        pLabel->setString(pString->getCString());
    }
    
    return pCell;
}

unsigned int TableViewLayer::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
}

void TableViewLayer::scrollViewDidScroll(CCScrollView* view)
{
}

void TableViewLayer::scrollViewDidZoom(CCScrollView* view)
{
}

void TableViewLayer::onEnter()
{
    CCLayer::onEnter();
}

void TableViewLayer::onExit()
{
    CCLayer::onExit();
}

