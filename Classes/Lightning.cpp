//
//  Lightning.cpp
//  hello
//
//  Created by ZeroYang on 7/10/14.
//
//

#include "Lightning.h"
#include <OpenGLES/ES1/gl.h>

USING_NS_CC;

int getNextRandom(unsigned long *seed)
{
	//taken off a linux site (linux.die.net)
	(*seed) = (*seed) * 1103515245 + 12345;
	return ((unsigned)((*seed)/65536)%32768);
}

cocos2d::CCPoint drawLightning(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint, int displace, int minDisplace, unsigned long randSeed){
	cocos2d::CCPoint mid = ccpMult(ccpAdd(beginPoint,endPoint), 0.5f);
    
	if (displace < minDisplace)
		ccDrawLine(beginPoint, endPoint);
	else
	{
		int r = getNextRandom(&randSeed);
		mid.x += (((r % 101)/100.0)-.5)*displace;
		r = getNextRandom(&randSeed);
		mid.y += (((r % 101)/100.0)-.5)*displace;
        
		drawLightning(beginPoint,mid,displace/2,minDisplace,randSeed);
		drawLightning(endPoint,mid,displace/2,minDisplace,randSeed);
        
	}
    
	return mid;
}

Lightning* Lightning::create(cocos2d::CCPoint beginPoint){
	Lightning* l = new Lightning;
	if(l && l->initWithStrikePoint(beginPoint)){
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return NULL;
}

Lightning* Lightning::create(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint){
	Lightning* l = new Lightning;
	if(l && l->initWithStrikePoint(beginPoint, endPoint)){
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return NULL;
}

bool Lightning::initWithStrikePoint(cocos2d::CCPoint beginPoint){
	return initWithStrikePoint(beginPoint, ccp(0, 0));
}

bool Lightning::initWithStrikePoint(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint){
	_beginePoint = beginPoint;
	_endPoint = endPoint;
	//_strikePoint3 = ccp(0, 0);
	_color = ccWHITE;
	_opacity = 255;
    
	srand(time(NULL));
	_seed = rand();
	_split = false;
    
	_displacement = 120;
	_minDisplacement = 4;
	_lighteningWidth = 1.0f;
    
	return true;
}

void Lightning::draw(){
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
    
	glColor4ub(_color.r, _color.g, _color.b, _opacity);
	glLineWidth(_lighteningWidth * CCRANDOM_0_1() * 4);
	glEnable(GL_LINE_SMOOTH);
    
	if (_opacity != 255)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	CCPoint mid = drawLightning(_beginePoint, _endPoint, _displacement, _minDisplacement, _seed);
//    CCPoint mid1 = drawLightning( ccpSub(_beginePoint, ccp(50, 100)), ccpAdd(_endPoint, ccp(100,100)), _displacement, _minDisplacement, _seed);
//    CCPoint mid2 = drawLightning(ccpSub(_beginePoint, ccp(100, 200)), ccpAdd(_endPoint, ccp(100,100)), _displacement, _minDisplacement, _seed);
//	CCPoint mid3 = drawLightning(ccpSub(_beginePoint, ccp(150, 400)), ccpAdd(_endPoint, ccp(100,100)), _displacement, _minDisplacement, _seed);
    ;
	if(_split) {
        drawLightning(mid, _endPoint, _displacement/2, _minDisplacement, _seed);
//        drawLightning(mid1, _endPoint, _displacement/2, _minDisplacement, _seed);
//        drawLightning(mid2, _endPoint, _displacement/2, _minDisplacement, _seed);
//        drawLightning(mid3, _endPoint, _displacement/2, _minDisplacement, _seed);
    }
    
	if (_opacity != 255)
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
}

void Lightning::setColor(const ccColor3B& color){
	_color = color;
}

const ccColor3B& Lightning::getColor(){
	return _color;
}

void Lightning::setOpacity(GLubyte opacity){
	_opacity = opacity;
}

GLubyte Lightning::getOpacity(){
	return _opacity;
}

void Lightning::strikeRandom(){
	srand(time(NULL));
	_seed = rand();
	this->strike();
}
CCArray* Lightning::getRGBAChildren() {
    return getChildren();
}
CCNode* Lightning::getRGBAParent() {
    return getParent();
}
void Lightning::strikeWithSeed(unsigned long seed){
	_seed = seed;
	this->strike();
}

void Lightning::strike(){
	this->setVisible(false);
	this->setOpacity(255);
    
	this->runAction(CCSequence::create(CCShow::create(), CCBlink::create(0.5f, 2), CCFadeOut::create(0.5f), NULL));
}
