//
//  BulletLayer.cpp
//  Warrior
//
//  Created by Varek Chai on 5/23/13.
//
//

#include "BulletLayer.h"
#include "PlaneManager.h"

#define MOVE_TIME_PLAYER               2.0f
#define MOVE_TIME_ENEMY1               7.0f
#define MOVE_TIME_ENEMY2               6.0f
#define MOVE_TIME_BOSS1                5.0f

#define MOVE_DISTANCE_PLAYER           (getWinSize().height)
#define MOVE_DISTANCE_ENEMY            (-getWinSize().height)

BulletLayer::BulletLayer()
{
    // init array
    //m_bulletsArray = CCArray::create();
    //m_bulletsArray->retain();
    
    m_bPlaneAlive = true;
}

BulletLayer::~BulletLayer()
{
    m_bulletsBatchNode->removeAllChildrenWithCleanup(true);
    this->removeChild(m_bulletsBatchNode, true);
    
    //m_bulletsArray->release();
}

BulletLayer* BulletLayer::create(E_PlaneType pt)
{
    BulletLayer *pRet = new BulletLayer();
    if (pRet && pRet->init(pt))
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

bool BulletLayer::init(E_PlaneType pt)
{
    if (BasicLayer::init())
    {
        m_planeType = pt;
        
        // set default value
        const char* bulletImgName = NULL;
        const char* bulletFrameName = NULL;
        CCRect rect;
        switch (m_planeType) {
            case e_pt_player:
                bulletImgName = "planebullet.png";
                bulletFrameName = SFN_BULLET_PLAYER;
                rect = CCRectMake(0, 0, 40, 43);
                m_moveTime = MOVE_TIME_PLAYER;
                m_moveDistance = MOVE_DISTANCE_PLAYER;
                break;
            case e_pt_enemy_1:
                bulletImgName = "enemyplanebullet.png";
                bulletFrameName = SFN_BULLET_ENEMY1;
                rect = CCRectMake(0, 0, 40, 40);
                m_moveTime = MOVE_TIME_ENEMY1;
                m_moveDistance = MOVE_DISTANCE_ENEMY;
                break;
            case e_pt_enemy_2:
                bulletImgName = "enemybullet2.png";
                bulletFrameName = SFN_BULLET_ENEMY2;
                rect = CCRectMake(0, 0, 29, 32);
                m_moveTime = MOVE_TIME_ENEMY2;
                m_moveDistance = MOVE_DISTANCE_ENEMY;
                break;
            case e_pt_enemy_boss1:
                bulletImgName = "bossbullet.png";
                bulletFrameName = SFN_BULLET_BOSS1;
                rect = CCRectMake(0, 0, 130, 60);
                m_moveTime = MOVE_TIME_BOSS1;
                m_moveDistance = MOVE_DISTANCE_ENEMY;
                break;
                
            default:
                break;
        }
        
        // add bullet png to CCSpriteFrameCatch
        //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(CCSpriteFrame::create(bulletImgName, rect), bulletFrameName);
        
        // init batch node
        m_bulletsBatchNode = CCSpriteBatchNode::create(bulletImgName);
        ccBlendFunc cb = {GL_SRC_ALPHA, GL_ONE};
        m_bulletsBatchNode->setBlendFunc(cb);
        
        // add batch node to layer
        this->addChild(m_bulletsBatchNode);
        
        // schedule move bullet
        //this->schedule(schedule_selector(BulletLayer::moveBullet), m_moveTimeInterval);
        
        return true;
    }
    return false;
}

void BulletLayer::setMoveSpeed(float moveTimeInterval, float moveDistance)
{
//    m_moveTimeInterval = moveTimeInterval;
//    m_moveDistance = moveDistance;
//    this->unschedule(schedule_selector(BulletLayer::moveBullet));
//    this->schedule(schedule_selector(BulletLayer::moveBullet), m_moveTimeInterval);
}

/*
void BulletLayer::addBullet(CCPoint pt)
{
    CCSprite* sp = CCSprite::createWithTexture(m_bulletsBatchNode->getTexture());
    
    sp->setPosition(pt);
    
    // add to array
    //m_bulletsArray->addObject(sp);
    
    // add to batch node
    m_bulletsBatchNode->addChild(sp);
    
    // move Bullet
    CCMoveBy* moveBy = CCMoveBy::create(m_moveTime, CCPointMake(0, m_moveDistance));
    
    // callback
    CCCallFuncN* callback = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::moveStopCallback));
    CCSequence* sequence = CCSequence::create(moveBy,callback,NULL);
    sp->runAction(sequence);
}
*/

void BulletLayer::addBullet(CCPoint pt)
{
    CCSprite* sp = CCSprite::createWithTexture(m_bulletsBatchNode->getTexture());
    sp->setPosition(pt);
    
    // add to batch node
    m_bulletsBatchNode->addChild(sp);
    
    CCMoveBy *moveBy = NULL;
    if (m_planeType == e_pt_player) {
        moveBy = CCMoveBy::create(m_moveTime, CCPointMake(0, m_moveDistance));
    }
    else {
        PlaneManager *mgr = (PlaneManager *)getParent();
        CCPoint ptPlayer = mgr->getPlayerPlanePosition();
        float x = ptPlayer.x - pt.x;
        float y = ptPlayer.y - pt.y;
        float c = sqrtf(x*x + y*y);
        float distance = sqrtf(1024*1024 + 768*768);
        float moveX = x*distance/c;
        float moveY = y*distance/c;
        
        moveBy = CCMoveBy::create(m_moveTime, CCPointMake(moveX, moveY));
    }
    
    // callback
    CCCallFuncN* callback = CCCallFuncN::create(this, callfuncN_selector(BulletLayer::moveStopCallback));
    CCSequence* sequence = CCSequence::create(moveBy,callback,NULL);
    sp->runAction(sequence);
}

/*
void BulletLayer::moveBullet(float t)
{
    float fVisiableCount = 0;
    CCObject* obj = NULL;
    CCArray *bulletArray = m_bulletsBatchNode->getChildren();
    CCARRAY_FOREACH(bulletArray, obj)
    {
        CCSprite* sp = (CCSprite*)obj;
        float fY = sp->getPositionY();
        //CCRect rc = CCRectMake(0, 0, getWinSize().width, getWinSize().height);
        //if (!rc.containsPoint(sp->getPosition()))
        if (fY <= 0 || fY >= getWinSize().height)
        {
            if (sp->isVisible()) {
                sp->setVisible(false);
            }
            //m_bulletsArray->removeObject(sp);
            //m_bulletsBatchNode->removeChild(sp, true);
        }else
        {
            // move the bullet
            sp->setPositionY(sp->getPositionY() + m_moveDistance);
            if (sp->isVisible()) {
                fVisiableCount++;
            }
        }
    }
    
    // check if can remove bullet layer
    if (!m_bPlaneAlive && fVisiableCount == 0) {
        this->unschedule(schedule_selector(BulletLayer::moveBullet));
        
        PlaneManager *parent = (PlaneManager *)getParent();
        parent->removeEnemyBullet(this);
    }
}
*/

CCArray* BulletLayer::getBulletsArray()
{
    return m_bulletsBatchNode->getChildren();
}

void BulletLayer::setPlaneAlive(bool t)
{
    m_bPlaneAlive = t;
}

void BulletLayer::moveStopCallback(CCNode *pSender)
{
    // set visiable false
    if (pSender->isVisible()) {
        pSender->setVisible(false);
    }
    
    float fVisiableCount = 0;
    CCObject* obj = NULL;
    CCArray *bulletArray = m_bulletsBatchNode->getChildren();
    CCARRAY_FOREACH(bulletArray, obj)
    {
        CCSprite* sp = (CCSprite*)obj;
        if (sp->isVisible()) {
            fVisiableCount++;
        }
    }
    
    // check if can remove bullet layer
    if (!m_bPlaneAlive && fVisiableCount == 0) {
        PlaneManager *parent = (PlaneManager *)getParent();
        parent->removeEnemyBullet(this);
    }
}
