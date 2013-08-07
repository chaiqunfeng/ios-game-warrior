//
//  PlaneLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#include "PlaneLayer.h"
#include "PlaneManager.h"
#include "MusicManager.h"

#define FIRE_INTERVAL_DEFAULT       0.2f
#define FIRE_INTERVAL_ENEMY1        (FIRE_INTERVAL_DEFAULT * 6)
#define FIRE_INTERVAL_ENEMY2        (FIRE_INTERVAL_DEFAULT * 5)
#define FIRE_INTERVAL_BOSS          (FIRE_INTERVAL_DEFAULT * 4)

PlaneLayer::PlaneLayer()
{
    m_fBlood = 1;
    m_bFireing = false;
    m_fireTimeInterval = FIRE_INTERVAL_DEFAULT;
}

PlaneLayer::~PlaneLayer()
{
}

PlaneLayer* PlaneLayer::create(E_PlaneType pt, BulletLayer* bullet)
{
    PlaneLayer *pRet = new PlaneLayer();
    if (pRet && pRet->init(pt, bullet))
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

bool PlaneLayer::init(E_PlaneType pt, BulletLayer* bullet)
{
    if (BasicLayer::init())
    {
        // get plane img name
        const char* szPlanImgName = NULL;
        switch (pt) {
            case e_pt_player:
                szPlanImgName = "plane.png";
                m_fBlood = BLOOD_PLAYER;
                m_fireTimeInterval = FIRE_INTERVAL_DEFAULT;
                
                break;
            case e_pt_enemy_1:
                szPlanImgName = "enemyplane.png";
                m_fBlood = BLOOD_ENEMY1;
                m_fireTimeInterval = FIRE_INTERVAL_ENEMY1;
                
                break;
            case e_pt_enemy_2:
                szPlanImgName = "enemyplanee2.png";
                m_fBlood = BLOOD_ENEMY2;
                m_fireTimeInterval = FIRE_INTERVAL_ENEMY2;
                
                break;
            case e_pt_enemy_boss1:
                szPlanImgName = "bossfirst.png";
                m_fBlood = BLOOD_BOSS1;
                m_fireTimeInterval = FIRE_INTERVAL_BOSS;
                
                break;
                
            default:
                break;
        }
        // create plane
        m_spPlane = CCSprite::create(szPlanImgName);
        if (m_spPlane)
        {
            m_spPlane->setPosition(ccp(getWinSize().width/2, getWinSize().height/2));
            this->addChild(m_spPlane, PLANE_ZORDER_LAYER);
        }
        
        // bullet layer is added to plane manager
        // here keeps the instance reference
        m_bulletLayer = bullet;
        
        m_type = pt;
        
        return true;
    }
    return false;
}

CCPoint PlaneLayer::getPlanePosition()
{
    if (m_spPlane)
    {
        return m_spPlane->getPosition();
    }
    else
    {
        return CCPointZero;
    }
}

CCRect PlaneLayer::getPlaneRect()
{
    if (m_spPlane)
    {
        return m_spPlane->boundingBox();
    }
    else
    {
        return CCRectZero;
    }
}

void PlaneLayer::fire()
{
    if (!m_bFireing)
    {
        m_bFireing = true;
        // schedule add bullet
        this->schedule(schedule_selector(PlaneLayer::addBullet), m_fireTimeInterval);
    }
}

void PlaneLayer::stopFire()
{
    if (m_bFireing)
    {
        m_bFireing = false;
        // unschedule add bullet
        this->unschedule(schedule_selector(PlaneLayer::addBullet));
    }
}

void PlaneLayer::addBullet(float t)
{
    if (m_bulletLayer)
    {
        if (m_type == e_pt_player) {
            MusicManager::sharedMusicManager()->shoot();
        }
        m_bulletLayer->addBullet(getPlanePosition());
    }
}

void PlaneLayer::setPlaneAlive(bool t)
{
    if (m_bulletLayer)
    {
        m_bulletLayer->setPlaneAlive(t);
    }
}

