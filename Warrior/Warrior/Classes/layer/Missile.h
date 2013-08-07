//
//  Missile.h
//  Warrior
//
//  Created by Varek Chai on 5/30/13.
//
//

#ifndef __Warrior__Missile__
#define __Warrior__Missile__

#include <iostream>
//#include "BasicLayer.h"
#include "UICommon.h"
#include "cocos2d.h"
USING_NS_CC;

class PlaneLayer;
class Missile:public CCSprite//BasicLayer
{
public:
    
    Missile();
    ~Missile();
    
    virtual bool init(E_PlaneType pt, PlaneLayer *target);
    static Missile *create(E_PlaneType pt, PlaneLayer *target);
    
    float           m_fBlood;
private:
    
    void directTarget(float t);
    
    CCSpriteBatchNode *m_bulletsBatchNode;
    
    PlaneLayer *m_targetPlane;
    E_PlaneType m_planeType;
};

#endif /* defined(__Warrior__Missile__) */
