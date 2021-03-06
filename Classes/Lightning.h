//
//  Lightning.h
//  hello
//
//  Created by ZeroYang on 7/10/14.
//
//

#ifndef __hello__Lightning__
#define __hello__Lightning__

#include "cocos2d.h"

extern int getNextRandom(unsigned long *seed);

extern cocos2d::CCPoint drawLightning(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint, int displace, int minDisplace, unsigned long randSeed);


class Lightning : public cocos2d::CCNode, public cocos2d::CCRGBAProtocol {
protected:
	cocos2d::ccColor3B _color;
	GLubyte _opacity;
    GLubyte		_displayedOpacity;
	cocos2d::ccColor3B	_displayedColor;
	bool		_cascadeOpacityEnabled, _cascadeColorEnabled;
public:
	bool initWithStrikePoint(cocos2d::CCPoint beginPoint);
	bool initWithStrikePoint(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint);
    
    static Lightning* create(cocos2d::CCPoint beginPoint);
    static Lightning* create(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint);
    
	void strikeRandom();
	void strikeWithSeed(unsigned long seed);
	void strike();
    
    
	virtual void draw();
    
	virtual void setColor(const cocos2d::ccColor3B& color);
	virtual const cocos2d::ccColor3B& getColor(void);
    
	virtual GLubyte getOpacity(void);
	virtual void setOpacity(GLubyte opacity);
    
    
    
	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCPoint, _beginePoint, BeginPoint);
	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCPoint, _endPoint, EndPoint);
	//CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCPoint, _strikePoint3, StrikePoint3);
    
	CC_SYNTHESIZE(bool, _split, Split);
    
	CC_SYNTHESIZE(int, _displacement, Displacement);
	CC_SYNTHESIZE(int, _minDisplacement, MinDisplacement);
	CC_SYNTHESIZE(float, _lighteningWidth, LighteningWidth);
    
	CC_SYNTHESIZE(unsigned long, _seed, Seed);
    
    cocos2d::CCArray* getRGBAChildren() ;
    cocos2d::CCNode* getRGBAParent() ;
    virtual const cocos2d::ccColor3B& getDisplayedColor(void) {
		return _displayedColor;
	}
	
    virtual GLubyte getDisplayedOpacity(void) {
		return _displayedOpacity;
	}
	
    
	
    virtual void setOpacityModifyRGB(bool bValue) {
	}
	
    virtual bool isOpacityModifyRGB(void) {
		return false;
	}
	
    virtual bool isCascadeColorEnabled(void) {
		return _cascadeColorEnabled;
	}
	virtual void setCascadeColorEnabled(bool cascadeColorEnabled) {
		_cascadeColorEnabled = cascadeColorEnabled;
	}
    virtual void updateDisplayedColor(const cocos2d::ccColor3B& parentColor) {
		_displayedColor.r = _color.r * parentColor.r/255.0;
		_displayedColor.g = _color.g * parentColor.g/255.0;
		_displayedColor.b = _color.b * parentColor.b/255.0;
		
		if (_cascadeColorEnabled)
		{
			CCObject *obj = NULL;
			CCARRAY_FOREACH(getRGBAChildren(), obj)
			{
				CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
				if (item)
				{
					item->updateDisplayedColor(_displayedColor);
				}
			}
		}
	}
    
    virtual bool isCascadeOpacityEnabled(void) {
		return _cascadeOpacityEnabled;
	}
	
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) {
		_cascadeOpacityEnabled = cascadeOpacityEnabled;
	}
	
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) {
		_displayedOpacity = _opacity * parentOpacity/255.0;
		
		if (_cascadeOpacityEnabled)
		{
			CCObject* pObj;
			CCARRAY_FOREACH(getRGBAChildren(), pObj)
			{
				CCRGBAProtocol* item = dynamic_cast<CCRGBAProtocol*>(pObj);
				if (item)
				{
					item->updateDisplayedOpacity(_displayedOpacity);
				}
			}
		}
	}
};

#endif /* defined(__hello__Lightning__) */
