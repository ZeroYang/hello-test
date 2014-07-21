//
//  LightLayer.cpp
//  hello
//
//  Created by ZeroYang on 7/16/14.
//
//

#include "LightLayer.h"


bool LightLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    m_light = CCSprite::create();
    m_light->setPosition(CCPointZero);
    m_light->setVisible(false);
    m_light->setContentSize(CCSize(100, 400));
    
    addChild(m_light);
    
    return true;
}

void LightLayer::light(CCPoint point)
{
    char name[64];
    int i = CCRANDOM_0_1()*4;
    sprintf(name, "lightning/%d.png", i+1);
    CCLog("%s", name);
    
    //for (int i = 0; i< 4; i++) {
        CCSprite *part1 = CCSprite::create("light.png");
//        CCSprite *part2 = CCSprite::create("lightning/2.png");
//        CCSprite *part3 = CCSprite::create("lightning/3.png");
//        CCSprite *part4 = CCSprite::create("lightning/4.png");
        

        //part1->setScaleX(0.2f);
//        part2->setScale(0.2f);
//        part3->setScale(0.2f);
//        part4->setScale(0.2f);
        
        part1->setPosition(ccp(part1->getContentSize().width/2, part1->getContentSize().height/2));
//        part2->setPosition(ccp(part1->getContentSize().width/2, i*part1->getContentSize().height/2+part2->getContentSize().height/2));
//        part3->setPosition(ccp(part1->getContentSize().width/2, i*part1->getContentSize().height/2+part2->getContentSize().height/2+part3->getContentSize().height/2));
//        part4->setPosition(ccp(part1->getContentSize().width/2, i*part1->getContentSize().height/2+part2->getContentSize().height/2+part3->getContentSize().height/2+part4->getContentSize().height/2));
        m_light->addChild(part1);
//        m_light->addChild(part2);
//        m_light->addChild(part3);
//        m_light->addChild(part4);
    //}

    
    //m_light->setTexture( CCSprite::create(name)->getTexture() );
    //m_light->setScale(0.5f);
    m_light->setPosition(point);
    m_light->runAction(CCSequence::create(CCShow::create(), CCBlink::create(0.5f, 2), CCFadeOut::create(0.5f), NULL));
}