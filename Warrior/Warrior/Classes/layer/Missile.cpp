//
//  Missile.cpp
//  Warrior
//
//  Created by Varek Chai on 5/30/13.
//
//

#include "Missile.h"
#include "PlaneLayer.h"

#define DIRECT_TIME_INTERVAL      0.1f


Missile::Missile()
{
}

Missile::~Missile()
{
}

Missile* Missile::create(E_PlaneType pt, PlaneLayer *target)
{
    Missile *pRet = new Missile();
    if (pRet && pRet->init(pt, target))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Missile::init(E_PlaneType pt, PlaneLayer *target)
{
    const char* szImgName = NULL;
    
    switch (pt) {
        case e_pt_player:
            szImgName = "planemissile.png";
            break;
            
        case e_pt_enemy_1:
        case e_pt_enemy_2:
        case e_pt_enemy_boss1:
            szImgName = "enemymissile.png";
            break;
            
        default:
            break;
    }
    
    if (CCSprite::initWithFile(szImgName))
    {
        m_fBlood = BLOOD_BOSS1_MISSILE;
        m_planeType = pt;
        m_targetPlane = target;
        float moveY = (pt == e_pt_player ? 100 : -100);
        CCMoveBy* moveBy = CCMoveBy::create(2.0f, ccp(0, moveY));
        runAction(moveBy);
        
        // schedule direct
        this->schedule(schedule_selector(Missile::directTarget), DIRECT_TIME_INTERVAL, kCCRepeatForever, 2.0f);
        
        return true;
    }
    
    return false;
}

void Missile::directTarget(float t)
{
    if (m_targetPlane) {
        
        stopAllActions();
        // direct move to player
        CCPoint ptTarget = m_targetPlane->getPlanePosition();
        float x = ptTarget.x - getPosition().x;
        float y = ptTarget.y - getPosition().y;
        float c = sqrtf(x*x + y*y);
        float distance = sqrtf(1024*1024 + 768*768);
        float moveX = x*distance/c;
        float moveY = y*distance/c;
        
        CCMoveBy* moveBy = CCMoveBy::create(5, ccp(moveX, moveY));
        runAction(moveBy);
    }
    
}
