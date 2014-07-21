//
//  LightLayer.h
//  hello
//
//  Created by ZeroYang on 7/16/14.
//
//

#ifndef __hello__LightLayer__
#define __hello__LightLayer__

#include "cocos2d.h"

USING_NS_CC;


class LightLayer : public CCLayer
{
public:
    bool init();
    
    void light(CCPoint point);
    
    CREATE_FUNC(LightLayer);
    
private:
    CCSprite *m_light;
};

#endif /* defined(__hello__LightLayer__) */
