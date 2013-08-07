//
//  BulletLayer.h
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#ifndef __Warrior__BulletLayer__
#define __Warrior__BulletLayer__

#include <iostream>
#include "BasicLayer.h"
#include "../UICommon.h"

class PlaneLayer;
class BulletLayer:public BasicLayer
{
public:
    
    BulletLayer();
    ~BulletLayer();
    
    virtual bool init(E_PlaneType pt);
    static BulletLayer* create(E_PlaneType pt);
    
    void addBullet(CCPoint pt);
    
    CCArray* getBulletsArray();
    
    void setMoveSpeed(float moveTimeInterval, float moveDistance);
    void setPlaneAlive(bool t);
    
private:
    
    //void moveBullet(float t);
    void moveStopCallback(CCNode *pSender);
    
    CCSpriteBatchNode* m_bulletsBatchNode;
    //CCArray* m_bulletsArray;
    
    E_PlaneType m_planeType;
    bool m_bPlaneAlive;
    
    float m_moveTime;
    float m_moveDistance;
};

#endif /* defined(__Warrior__BulletLayer__) */
