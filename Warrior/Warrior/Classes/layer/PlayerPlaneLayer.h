//
//  WarriorLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#ifndef __Warrior__PlayerPlaneLayer__
#define __Warrior__PlayerPlaneLayer__

#include <iostream>
#include "PlaneLayer.h"

class PlayerPlaneLayer:public PlaneLayer
{
public:
    
    PlayerPlaneLayer();
    ~PlayerPlaneLayer();
    
    virtual bool init(BulletLayer* bullet);
    static PlayerPlaneLayer* create(BulletLayer* bullet);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    
};

#endif /* defined(__Warrior__PlayerPlaneLayer__) */
