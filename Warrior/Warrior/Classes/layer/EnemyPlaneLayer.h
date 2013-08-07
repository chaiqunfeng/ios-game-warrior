//
//  EnemyPlaneLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/24/13.
//
//

#ifndef __Warrior__EnemyPlaneLayer__
#define __Warrior__EnemyPlaneLayer__

#include <iostream>
#include "PlaneLayer.h"

class EnemyPlaneLayer:public PlaneLayer
{
public:
    
    EnemyPlaneLayer();
    ~EnemyPlaneLayer();
    
    virtual bool init(E_PlaneType pt, BulletLayer* bullet);
    static EnemyPlaneLayer* create(E_PlaneType pt, BulletLayer* bullet);
        
    void updateBossBlood();

private:
    
    void performFire(float t);
    void addMissile(float t);
    
    void moveEnemy1(float t);
    //void moveEnemy2(float t);
    void moveBoss1_1(float t);
    void moveBoss1_2(float t);
    void moveStopCallback();
    void helpCallback(float t);
    
    CCSprite* m_spBossBlood;
};

#endif /* defined(__Warrior__EnemyPlaneLayer__) */
