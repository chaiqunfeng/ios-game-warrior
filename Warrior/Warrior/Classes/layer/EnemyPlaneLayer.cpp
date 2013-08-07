//
//  EnemyPlane.cpp
//  Warrior
//
//  Created by Varek Chai on 5/24/13.
//
//

#include "EnemyPlaneLayer.h"
#include "PlaneManager.h"

#define DEFAULT_PLANE_STAYTIME          2.0f
#define DEFAULT_PLANE_MOVETIME          4.0f

#define DEFAULT_PLANE1_SHOWTIME         3.0f

#define DEFAULT_PLANE2_SHOWTIME         3.0f

#define DEFAULT_BOSS1_SHOWTIME          1.0f
//#define DEFAULT_BOSS1_MOVETIME          10.0f
#define DEFAULT_BOSS1_MOVETIME_FAST     0.1f
#define DEFAULT_BOSS1_MOVETIME_SLOW     0.5f

#define DEFAULT_BOSS1_ADDMISSILE_TIME   10.0f

//#define BLOOD_BG_BOSS                "blood_bg600_10.png"
//#define BLOOD_RED_BOSS               "blood_red600_10.png"
//#define BLOOD_BLUE_BOSS              "blood_blue600_10.png"
#define BLOOD_BG_BOSS              "blood_bg238_5.png"
#define BLOOD_RED_BOSS             "blood_red238_5.png"
#define BLOOD_BLUE_BOSS            "blood_blue238_5.png"

EnemyPlaneLayer::EnemyPlaneLayer()
{
}

EnemyPlaneLayer::~EnemyPlaneLayer()
{
}

EnemyPlaneLayer* EnemyPlaneLayer::create(E_PlaneType pt, BulletLayer* bullet)
{
    EnemyPlaneLayer *pRet = new EnemyPlaneLayer();
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

bool EnemyPlaneLayer::init(E_PlaneType pt, BulletLayer* bullet)
{
    if (PlaneLayer::init(pt, bullet))
    {
        m_spBossBlood = NULL;
        
        // move plane logic
        switch (pt)
        {
            case e_pt_player:
                break;
                
            case e_pt_enemy_1:
            {
                float randomX = CCRANDOM_0_1() * getWinSize().width;
                float randomY = CCRANDOM_0_1() * getWinSize().height;
                float randomStartX = CCRANDOM_0_1() > 0.5f ? getWinSize().width : 0;
                float randomStartY = CCRANDOM_0_1() * getWinSize().height;
                m_spPlane->setPosition(ccp(randomStartX, randomStartY));
                CCMoveTo* moveTo = CCMoveTo::create(DEFAULT_PLANE1_SHOWTIME, CCPointMake(randomX, randomY));
                m_spPlane->runAction(moveTo);
                
                this->scheduleOnce(schedule_selector(EnemyPlaneLayer::moveEnemy1), DEFAULT_PLANE1_SHOWTIME+DEFAULT_PLANE_STAYTIME);
                
                // fire
                this->scheduleOnce(schedule_selector(EnemyPlaneLayer::performFire), DEFAULT_PLANE1_SHOWTIME);
            }
                break;
                
            case e_pt_enemy_2:
            {
                float randomX = CCRANDOM_0_1() * getWinSize().width;
                float randomY = CCRANDOM_0_1() * getWinSize().height;
                m_spPlane->setPosition(ccp(randomX, getWinSize().height));
                CCMoveTo* moveTo = CCMoveTo::create(DEFAULT_PLANE2_SHOWTIME, CCPointMake(randomX, randomY));
                CCMoveBy* moveBy = CCMoveBy::create(DEFAULT_PLANE_STAYTIME, CCPointMake(0, 0));
                CCMoveBy* moveBy2 = CCMoveBy::create(DEFAULT_PLANE_MOVETIME, CCPointMake(0, - getWinSize().height));
                
                // callback
                CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(EnemyPlaneLayer::moveStopCallback));
                
                CCSequence* sequence = CCSequence::create(moveTo,moveBy,moveBy2,callback,NULL);
                m_spPlane->runAction(sequence);
                
                // fire
                this->scheduleOnce(schedule_selector(EnemyPlaneLayer::performFire), DEFAULT_PLANE2_SHOWTIME);
            }
                break;
                
            case e_pt_enemy_boss1:
            {
                m_spPlane->setPosition(ccp(getWinSize().width/2, getWinSize().height));
                CCMoveBy* moveBy = CCMoveBy::create(DEFAULT_BOSS1_SHOWTIME, CCPointMake(0, -150));
                CCMoveBy* moveBy2 = CCMoveBy::create(DEFAULT_PLANE_STAYTIME, CCPointMake(0, 0));
                CCSequence* sequence = CCSequence::create(moveBy,moveBy2,NULL);
                m_spPlane->runAction(sequence);
                
                // move
                this->schedule(schedule_selector(EnemyPlaneLayer::moveBoss1_1), (DEFAULT_BOSS1_MOVETIME_SLOW + DEFAULT_BOSS1_MOVETIME_FAST) * 20 + DEFAULT_PLANE_STAYTIME);
                
                // fire
                this->scheduleOnce(schedule_selector(EnemyPlaneLayer::performFire), DEFAULT_BOSS1_SHOWTIME);
                
                // schedule missile
                this->schedule(schedule_selector(EnemyPlaneLayer::addMissile), DEFAULT_BOSS1_ADDMISSILE_TIME);
                
                // add boss blood
                CCLabelTTF* labelBlood = CCLabelTTF::create("BOSS", "", 20.0f);
                labelBlood->setAnchorPoint(ccp(0, 0.5f));
                labelBlood->setPosition(ccp(getWinSize().width / 2 + 80, getWinSize().height - 50));
                this->addChild(labelBlood);
                
                CCSprite * spBloodBG = CCSprite::create(BLOOD_BG_BOSS);
                if (spBloodBG)
                {
                    //spBloodBG->setOpacity(100);
                    spBloodBG->setAnchorPoint(ccp(0, 0.5f));
                    spBloodBG->setPosition(ccp(getWinSize().width / 2 + 140, getWinSize().height - 50));
                    this->addChild(spBloodBG, MIN_ZORDER);
                }
                
                m_spBossBlood = CCSprite::create(BLOOD_BLUE_BOSS);
                if (m_spBossBlood)
                {
                    //m_spBossBlood->setOpacity(100);
                    m_spBossBlood->setAnchorPoint(ccp(0, 0.5f));
                    m_spBossBlood->setPosition(ccp(getWinSize().width / 2 + 140, getWinSize().height - 50));
                    this->addChild(m_spBossBlood, MIN_ZORDER);
                }
            }
                break;
                
            default:
                break;
        }
        
        return true;
    }
    return false;
}

void EnemyPlaneLayer::updateBossBlood()
{
    if (m_spBossBlood) {
        m_spBossBlood->removeFromParentAndCleanup(true);
        CCRect rc = CCRectMake(0, 0, 238 * m_fBlood / BLOOD_BOSS1, 5);
        m_spBossBlood = CCSprite::create(BLOOD_BLUE_BOSS, rc);
        
        if (m_spBossBlood) {
            //m_spBossBlood->setOpacity(100);
            m_spBossBlood->setAnchorPoint(ccp(0,0.5f));
            m_spBossBlood->setPosition(ccp(getWinSize().width / 2 + 140, getWinSize().height - 50));
            this->addChild(m_spBossBlood, PLANE_ZORDER_LAYER);
        }
        
        if (m_fBlood <= BLOOD_BOSS1 / 5) {
            this->schedule(schedule_selector(EnemyPlaneLayer::helpCallback), m_fBlood * 1.0f / BLOOD_BOSS1);
        }
        else
        {
            this->unschedule(schedule_selector(EnemyPlaneLayer::helpCallback));
            m_spBossBlood->setVisible(true);
        }
    }
}

void EnemyPlaneLayer::helpCallback(float t)
{
    m_spBossBlood->setVisible(!m_spBossBlood->isVisible());
}

void EnemyPlaneLayer::performFire(float t)
{
    fire();
}

void EnemyPlaneLayer::addMissile(float t)
{
    PlaneManager *mgr = (PlaneManager *)getParent();
    CCPoint pt = getPlanePosition();
    CCRect rc = getPlaneRect();
    mgr->addMissile(ccp(pt.x - rc.size.width / 4, pt.y), m_type);
    mgr->addMissile(ccp(pt.x + rc.size.width / 4, pt.y), m_type);
    mgr->addMissile(ccp(pt.x - rc.size.width / 2, pt.y), m_type);
    mgr->addMissile(ccp(pt.x + rc.size.width / 2, pt.y), m_type);
}

void EnemyPlaneLayer::moveEnemy1(float t)
{
    PlaneManager *mgr = (PlaneManager *)getParent();
    CCPoint ptPlayer = mgr->getPlayerPlanePosition();
    CCPoint ptEnemy = getPlanePosition();
    float x = ptPlayer.x - ptEnemy.x;
    float y = ptPlayer.y - ptEnemy.y;
    float c = sqrtf(x*x + y*y);
    float distance = sqrtf(1024*1024 + 768*768);
    float moveX = x*distance/c;
    float moveY = y*distance/c;
    
    CCMoveBy* moveBy = CCMoveBy::create(DEFAULT_PLANE_MOVETIME, CCPointMake(moveX, moveY));
    
    // callback
    CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(EnemyPlaneLayer::moveStopCallback));
    
    m_spPlane->runAction(CCSequence::create(moveBy,callback,NULL));
}

//void EnemyPlaneLayer::moveEnemy2(float t)
//{
//}

void EnemyPlaneLayer::moveBoss1_1(float t)
{
    CCMoveBy* moveLeftSlow = CCMoveBy::create(DEFAULT_BOSS1_MOVETIME_SLOW, CCPointMake(-getWinSize().width/2, 0));
    CCMoveBy* moveLeftFast = CCMoveBy::create(DEFAULT_BOSS1_MOVETIME_FAST, CCPointMake(-getWinSize().width/2, 0));
    CCMoveBy* moveRightSlow = CCMoveBy::create(DEFAULT_BOSS1_MOVETIME_SLOW, CCPointMake(getWinSize().width/2, 0));
    CCMoveBy* moveRightFast = CCMoveBy::create(DEFAULT_BOSS1_MOVETIME_FAST, CCPointMake(getWinSize().width/2, 0));
    
    CCSequence* sequence = CCSequence::create(moveLeftSlow,
                                              moveRightSlow,moveRightSlow,moveLeftSlow,moveLeftSlow,
                                              moveRightSlow,moveRightSlow,moveLeftSlow,moveLeftSlow,
                                              moveRightSlow,moveRightSlow,moveLeftSlow,moveLeftSlow,
                                              moveRightFast,moveRightFast,moveLeftFast,moveLeftFast,
                                              moveRightFast,moveRightFast,moveLeftFast,moveLeftFast,
                                              moveRightFast,moveRightFast,moveLeftFast,moveLeftFast,
                                              moveRightSlow,moveRightFast,moveLeftSlow,moveLeftFast,
                                              moveRightFast,moveRightSlow,moveLeftFast,moveLeftSlow,
                                              moveRightSlow,moveRightFast,moveLeftSlow,moveLeftFast,
                                              moveRightFast,moveRightSlow,moveLeftFast,NULL
                                              );
    m_spPlane->runAction(sequence);
}

void EnemyPlaneLayer::moveBoss1_2(float t)
{
}

void EnemyPlaneLayer::moveStopCallback()
{
    stopFire();
    setPlaneAlive(false);
    PlaneManager *parent = (PlaneManager *)getParent();
    parent->removeEnemy(this);
}