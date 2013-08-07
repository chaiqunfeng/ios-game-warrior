//
//  PlaneLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#ifndef __Warrior__PlaneLayer__
#define __Warrior__PlaneLayer__

#include <iostream>
#include "BasicLayer.h"
#include "BulletLayer.h"
#include "UICommon.h"

class BulletLayer;
class PlaneLayer:public BasicLayer
{
public:
    
    PlaneLayer();
    ~PlaneLayer();
    
    virtual bool init(E_PlaneType pt, BulletLayer* bullet);
    static PlaneLayer *create(E_PlaneType pt, BulletLayer* bullet);
    
    CCPoint     getPlanePosition();
    CCRect      getPlaneRect();
    
    void fire();
    void stopFire();
    void setPlaneAlive(bool t);
    
    float           m_fBlood;
    E_PlaneType     m_type;
protected:
    
    void addBullet(float t);
    void moveBullet(float t);
    
    CCSprite* m_spPlane;
    BulletLayer* m_bulletLayer;
    
    bool m_bFireing;
    
    float m_fireTimeInterval;
};

#endif /* defined(__Warrior__PlaneLayer__) */
