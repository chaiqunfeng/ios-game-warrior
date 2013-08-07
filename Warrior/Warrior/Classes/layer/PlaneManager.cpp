//
//  PlaneManager.cpp
//  Warrior
//
//  Created by Varek Chai on 5/27/13.
//
//

#include "PlaneManager.h"
#include "PlaneLayer.h"
#include "Effects.h"
#include "GamingLayer.h"
#include "TimerLabel.h"
#include "ScoreLabel.h"
#include "GameOverLayer.h"
#include "ArchiveManager.h"
#include "MusicManager.h"
#include "Medicine.h"
#include "Missile.h"

#define HITCHECK_TIME_INTERVAL       0.01f
#define BLOOD_BG_PLAYER              "blood_bg238_5.png"
#define BLOOD_RED_PLAYER             "blood_red238_5.png"
#define BLOOD_BLUE_PLAYER            "blood_blue238_5.png"

PlaneManager::PlaneManager()
{
    // init array
    m_enemyArray = CCArray::create();
    m_enemyArray->retain();
    
    m_enemyBulletArray = CCArray::create();
    m_enemyBulletArray->retain();
    
    m_enemyMissileArray = CCArray::create();
    m_enemyMissileArray->retain();
    
    m_medicineArray = CCArray::create();
    m_medicineArray->retain();
}

PlaneManager::~PlaneManager()
{
    m_enemyArray->release();
    m_enemyBulletArray->release();
    m_enemyMissileArray->release();
    m_medicineArray->release();
}

bool PlaneManager::init()
{
    if (BasicLayer::init())
    {
        startGame();
        return true;
    }
    return false;
}

void PlaneManager::startGame()
{
    // blood label
    CCLabelTTF* labelBlood = CCLabelTTF::create("血量", "", 20.0f);
    labelBlood->setAnchorPoint(ccp(0, 0.5f));
    labelBlood->setPosition(ccp(getWinSize().width / 2 + 80, getWinSize().height - 20));
    this->addChild(labelBlood);
    
    // add player plane blood
    CCSprite * spBloodBG = CCSprite::create(BLOOD_BG_PLAYER);
    if (spBloodBG)
    {
        //spBloodBG->setOpacity(100);
        spBloodBG->setAnchorPoint(ccp(0,0.5f));
        spBloodBG->setPosition(ccp(getWinSize().width / 2 + 140, getWinSize().height - 20));
        this->addChild(spBloodBG, MIN_ZORDER);
    }
    
    m_spPlayerBlood = CCSprite::create(BLOOD_RED_PLAYER);
    if (m_spPlayerBlood)
    {
        //m_spPlayerBlood->setOpacity(100);
        m_spPlayerBlood->setAnchorPoint(ccp(0,0.5f));
        m_spPlayerBlood->setPosition(ccp(getWinSize().width / 2 + 140, getWinSize().height - 20));
        this->addChild(m_spPlayerBlood, MIN_ZORDER);
    }
    
    // add player plane bullet
    m_playerBullet = BulletLayer::create(e_pt_player);
    this->addChild(m_playerBullet,PLANE_ZORDER_LAYER);
    
    // add player plane
    m_playerPlane = PlayerPlaneLayer::create(m_playerBullet);
    this->addChild(m_playerPlane,PLANE_ZORDER_LAYER);
    
    // add enemy1 plane
    this->schedule(schedule_selector(PlaneManager::addEnemy1Plane), 4.0f);
    
    // add enemy2 plane
    this->schedule(schedule_selector(PlaneManager::addEnemy2Plane), 5.0f);
    
    // add boss plane
    this->scheduleOnce(schedule_selector(PlaneManager::performAddBossPlane), 25.0f);
    
    // hit judge
    this->schedule(schedule_selector(PlaneManager::hitCheck), HITCHECK_TIME_INTERVAL);
    
    // add medicine
    this->schedule(schedule_selector(PlaneManager::addMedicine), 5.0f);
}

CCPoint PlaneManager::getPlayerPlanePosition()
{
    if (m_playerPlane)
    {
        return m_playerPlane->getPlanePosition();
    }
    
    return CCPointZero;
}

void PlaneManager::removeEnemy(CCNode* enemy)
{
    m_enemyArray->removeObject(enemy);
    removeChild(enemy, true);
}

void PlaneManager::removeEnemyBullet(CCNode* enemyBullet)
{
    m_enemyBulletArray->removeObject(enemyBullet);
    removeChild(enemyBullet, true);
}

void PlaneManager::removeMedicine(CCNode* medicine)
{
    m_medicineArray->removeObject(medicine);
    removeChild(medicine, true);
}

void PlaneManager::setPlayerTouchEnabled(bool t)
{
    if (m_playerPlane)
    {
        m_playerPlane->setTouchEnabled(t);
    }
}

void PlaneManager::addMissile(CCPoint po, E_PlaneType pt)
{
    if (!m_playerPlane) {
        return;
    }
    
    if (pt != e_pt_player) {
        Missile *missile = Missile::create(pt, m_playerPlane);
        if (missile) {
            missile->setPosition(po);
            this->addChild(missile);
            m_enemyMissileArray->addObject(missile);
        }
    }
    else {
        //TODO:
    }
}

void PlaneManager::addEnemy1Plane(float t)
{
    // add enemy plane bullet
    BulletLayer *bullet = BulletLayer::create(e_pt_enemy_1);
    this->addChild(bullet,PLANE_ZORDER_LAYER);
    m_enemyBulletArray->addObject(bullet);
    
    // add enemy plane
    EnemyPlaneLayer *ep = EnemyPlaneLayer::create(e_pt_enemy_1, bullet);
    this->addChild(ep, PLANE_ZORDER_LAYER);
    m_enemyArray->addObject(ep);
}

void PlaneManager::addEnemy2Plane(float t)
{
    // add enemy plane bullet
    BulletLayer *bullet = BulletLayer::create(e_pt_enemy_2);
    this->addChild(bullet, PLANE_ZORDER_LAYER);
    m_enemyBulletArray->addObject(bullet);
    
    // add enemy plane
    EnemyPlaneLayer* ep = EnemyPlaneLayer::create(e_pt_enemy_2, bullet);
    this->addChild(ep, PLANE_ZORDER_LAYER);
    m_enemyArray->addObject(ep);
}

void PlaneManager::performAddBossPlane(float t)
{
    // add boss plane bullet
    BulletLayer *bullet = BulletLayer::create(e_pt_enemy_boss1);
    this->addChild(bullet, PLANE_ZORDER_LAYER);
    m_enemyBulletArray->addObject(bullet);
    
    // add boss plane
    EnemyPlaneLayer* ep = EnemyPlaneLayer::create(e_pt_enemy_boss1, bullet);
    this->addChild(ep, PLANE_ZORDER_LAYER);
    m_enemyArray->addObject(ep);
}

void PlaneManager::addMedicine(float t)
{
    // average 15s a medicine, 60s a big medicion
    float random = CCRANDOM_0_1();
    
    if (random > 0.33f) {
        return;
    }
    
    Medicine *medicine = Medicine::create(random < 0.083f? false: true);
    this->addChild(medicine, PLANE_ZORDER_LAYER);
    m_medicineArray->addObject(medicine);
    
    // move it
    // direction is the middle point between player and center
    CCPoint ptPlayer = getPlayerPlanePosition();
    CCPoint ptDest = ccp((ptPlayer.x + getWinSize().width / 2) / 2, (ptPlayer.y + getWinSize().height / 2) / 2);
    float x = ptDest.x - medicine->getPosition().x;
    float y = ptDest.y - medicine->getPosition().y;
    float c = sqrtf(x*x + y*y);
    float distance = sqrtf(1024*1024 + 768*768);
    float moveX = x*distance/c;
    float moveY = y*distance/c;
    
    CCMoveBy* moveBy = CCMoveBy::create(30, ccp(moveX, moveY));
    medicine->runAction(moveBy);
}

void PlaneManager::gameOver()
{
    CCLOG("Game over!!!!!!!!!!!!!!!!!!");
    // remove player plane
    if (m_playerPlane)
    {
        m_playerPlane->removeFromParentAndCleanup(true);
        m_playerPlane = NULL;
    }
    
    // stop game duration timer
    GamingLayer *parent = (GamingLayer *)getParent();
    TimerLabel *timer = (TimerLabel *)parent->getChildByTag(GAMING_TAG_LABEL_TIMER);
    timer->stopTimer();
    
    ScoreLabel *score = (ScoreLabel *)parent->getChildByTag(GAMING_TAG_LABEL_SCORE);
    
    struct cocos2d::cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    time_t timeS = now.tv_sec + now.tv_usec /1000000.0;
    
    // set record of game over layer
    GameOverLayer *gameover = (GameOverLayer *)parent->getChildByTag(GAMEOVER_TAG_LAYER);
    gameover->setGameResult(score->getScore(), timer->getDuration(), timeS);
    
    // save record to db
    ArchiveManager *archive = ArchiveManager::sharedArchiveManager();
    ArchiveItem item1 = {score->getScore(),timer->getDuration(),timeS};
    archive->addItem(&item1);
    
    parent->gameoverCallback();
}

void PlaneManager::hitCheck(float t)
{
    if (m_enemyArray->count() == 0 || !m_playerPlane)
    {
        return;
    }
    
    CCPoint pointPlayer = m_playerPlane->getPlanePosition();
    
    // check enemy - player/player's bullet
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_enemyArray, obj)
    {
        EnemyPlaneLayer* ep = (EnemyPlaneLayer*)obj;
        CCRect rectEnemy = ep->getPlaneRect();
        
        if (m_playerPlane && m_playerPlane->m_fBlood > 0 && ep && ep->m_fBlood > 0)
        {
            // check enemy - player
            // suppose player size is (20,20)
            CCRect rectTemp = rectEnemy;
            rectTemp.origin.x -= 10;
            rectTemp.origin.y -= 10;
            rectTemp.size.width += 20;
            rectTemp.size.height += 20;
            if (rectTemp.containsPoint(pointPlayer))
            {
                MusicManager::sharedMusicManager()->bomb();
                ///bool intersectsRect (const CCRect & rect) const
                if (ep->m_type == e_pt_enemy_boss1) {
                    Effects::sharedEffects()->boom(this, m_playerPlane->getPlanePosition());
                    // hit to boss, and game over
                    m_playerPlane->m_fBlood = 0;
                    changePlayerBloodTip(-BLOOD_PLAYER);
                }
                else {
                    Effects::sharedEffects()->boom(this, ep->getPlanePosition());
                    m_playerPlane->m_fBlood -= DEMAGE_ENEMY_PLANE;
                    changePlayerBloodTip(-DEMAGE_ENEMY_PLANE);
                    // enemy will be killed by hit at once
                    ep->m_fBlood = 0;
                }
                
                updatePlayerBlood();
                
                if (ep && ep->m_fBlood <= 0)
                {
                    CCLOG("Killed one enemy!!!!!!!!!!!!!!!!!!");
                    ep->stopFire();
                    ep->setPlaneAlive(false);
                    m_enemyArray->removeObject(ep);
                    ep->removeFromParentAndCleanup(true);
                    ep = NULL;
                    
                    GamingLayer *parent = (GamingLayer *)getParent();
                    ScoreLabel *score = (ScoreLabel *)parent->getChildByTag(GAMING_TAG_LABEL_SCORE);
                    score->updateScore();
                }
                if (m_playerPlane && m_playerPlane->m_fBlood <= 0)
                {
                    gameOver();
                }
            }
        }
        
        if (ep && ep->m_fBlood > 0)
        {
            // check enemy - player's bullet
            CCObject* obj2 = NULL;
            CCPoint pointEnemy = ep->getPlanePosition();
            CCArray* array = m_playerBullet->getBulletsArray();
            CCARRAY_FOREACH(array, obj2)
            {
                if (ep && ep->m_fBlood > 0)
                {
                    CCSprite* bulletPlayer = (CCSprite*)obj2;
                    CCRect rectPlayerBullet = bulletPlayer->boundingBox();
                    rectPlayerBullet.origin.x -= rectEnemy.size.width/2;
                    rectPlayerBullet.origin.y -= rectEnemy.size.height/2;
                    rectPlayerBullet.size.width += rectEnemy.size.width;
                    rectPlayerBullet.size.height += rectEnemy.size.height;
                    
                    if (bulletPlayer->isVisible() && rectPlayerBullet.containsPoint(pointEnemy))
                    {
                        MusicManager::sharedMusicManager()->bomb();
                        Effects::sharedEffects()->boom(this, bulletPlayer->getPosition());
                        
                        bulletPlayer->setVisible(false);
                        //array->removeObject(bulletPlayer);
                        //bulletPlayer->removeFromParentAndCleanup(true);
                        //bulletPlayer = NULL;
                        
                        ep->m_fBlood -= DEMAGE_PLAYER_BULLET;
                        if (ep->m_type == e_pt_enemy_boss1) {
                            ((EnemyPlaneLayer *)ep)->updateBossBlood();
                        }
                        if (ep && ep->m_fBlood <= 0)
                        {
                            CCLOG("Killed one enemy!!!!!!!!!!!!!!!!!!");
                            ep->stopFire();
                            ep->setPlaneAlive(false);
                            m_enemyArray->removeObject(ep);
                            ep->removeFromParentAndCleanup(true);
                            ep = NULL;
                            
                            GamingLayer *parent = (GamingLayer *)getParent();
                            ScoreLabel *score = (ScoreLabel *)parent->getChildByTag(GAMING_TAG_LABEL_SCORE);
                            score->updateScore();
                        }
                    }
                }
                
            }
        }
    }
    
    // check player - enemy's bullet
    obj = NULL;
    CCARRAY_FOREACH(m_enemyBulletArray, obj)
    {
        if (m_playerPlane && m_playerPlane->m_fBlood > 0)
        {
            // suppose player size is (20,20)
            CCObject* obj2 = NULL;
            BulletLayer * bulletLayer = (BulletLayer *)obj;
            CCArray* array = bulletLayer->getBulletsArray();
            CCARRAY_FOREACH(array, obj2)
            {
                if (m_playerPlane && m_playerPlane->m_fBlood > 0)
                {
                    CCSprite* bulletEnemy = (CCSprite*)obj2;
                    CCRect rectEnemyBullet = bulletEnemy->boundingBox();
                    rectEnemyBullet.origin.x -= 10;
                    rectEnemyBullet.origin.y -= 10;
                    rectEnemyBullet.size.width += 20;
                    rectEnemyBullet.size.height += 20;
                    if (bulletEnemy->isVisible() && rectEnemyBullet.containsPoint(pointPlayer))
                    {
                        MusicManager::sharedMusicManager()->bomb();
                        Effects::sharedEffects()->boom(this, bulletEnemy->getPosition());
                        
                        //array->removeObject(bulletEnemy);
                        //bulletEnemy->removeFromParentAndCleanup(true);
                        //bulletEnemy = NULL;
                        bulletEnemy->setVisible(false);
                        
                        m_playerPlane->m_fBlood -= DEMAGE_ENEMY_BULLET;
                        changePlayerBloodTip(-DEMAGE_ENEMY_BULLET);
                        updatePlayerBlood();
                        if (m_playerPlane && m_playerPlane->m_fBlood <= 0)
                        {
                            gameOver();
                        }
                    }
                }
                
            }
        }
    }
    
    // check player - medicine
    obj = NULL;
    CCARRAY_FOREACH(m_medicineArray, obj)
    {
        Medicine *medicine = (Medicine *)obj;
        if (m_playerPlane && m_playerPlane->m_fBlood > 0 && medicine && !medicine->isReceived())
        {
            // suppose player size is (40, 40)
            CCRect rectTemp = medicine->boundingBox();;
            rectTemp.origin.x -= 20;
            rectTemp.origin.y -= 20;
            rectTemp.size.width += 40;
            rectTemp.size.height += 40;
            if (rectTemp.containsPoint(pointPlayer))
            {
                medicine->setReceived();
                m_playerPlane->m_fBlood += medicine->bloodCapacity();
                changePlayerBloodTip(medicine->bloodCapacity());
                if (m_playerPlane->m_fBlood > BLOOD_PLAYER) {
                    m_playerPlane->m_fBlood = BLOOD_PLAYER;
                }
                
                updatePlayerBlood();
            }
        }
    }
    
    // check missile - player/player's bullet
    obj = NULL;
    CCARRAY_FOREACH(m_enemyMissileArray, obj)
    {
        Missile *missile = (Missile *)obj;
        // check missile - player
        if (m_playerPlane && m_playerPlane->m_fBlood > 0 && missile && missile->m_fBlood > 0)
        {
            // suppose player size is (20, 20)
            CCRect rectTemp = missile->boundingBox();;
            rectTemp.origin.x -= 10;
            rectTemp.origin.y -= 10;
            rectTemp.size.width += 20;
            rectTemp.size.height += 20;
            if (rectTemp.containsPoint(pointPlayer))
            {
                MusicManager::sharedMusicManager()->bomb();
                
                
                Effects::sharedEffects()->boom(this, missile->getPosition());
                m_playerPlane->m_fBlood -= DEMAGE_BOSS1_MISSILE;
                changePlayerBloodTip(-DEMAGE_BOSS1_MISSILE);
                updatePlayerBlood();
                
                CCLOG("Killed one missile!!!!!!!!!!!!!!!!!!");
                // missile will be killed by hit at once
                missile->m_fBlood = 0;
                m_enemyMissileArray->removeObject(missile);
                missile->removeFromParentAndCleanup(true);
                missile = NULL;
                
                if (m_playerPlane && m_playerPlane->m_fBlood <= 0)
                {
                    gameOver();
                }
            }
        }
        
        if (missile && missile->m_fBlood > 0)
        {
            // check missile - player's bullet
            CCObject* obj2 = NULL;
            CCPoint pointTemp = missile->getPosition();
            CCArray* array = m_playerBullet->getBulletsArray();
            CCARRAY_FOREACH(array, obj2)
            {
                if (missile && missile->m_fBlood > 0)
                {
                    CCSprite* bulletPlayer = (CCSprite*)obj2;
                    CCRect rectPlayerBullet = bulletPlayer->boundingBox();
                    CCRect rectMissile = missile->boundingBox();
                    rectPlayerBullet.origin.x -= rectMissile.size.width/2;
                    rectPlayerBullet.origin.y -= rectMissile.size.height/2;
                    rectPlayerBullet.size.width += rectMissile.size.width;
                    rectPlayerBullet.size.height += rectMissile.size.height;
                    
                    if (bulletPlayer->isVisible() && rectPlayerBullet.containsPoint(pointTemp))
                    {
                        MusicManager::sharedMusicManager()->bomb();
                        Effects::sharedEffects()->boom(this, bulletPlayer->getPosition());
                        missile->m_fBlood -= DEMAGE_PLAYER_BULLET;
                        
                        if (missile && missile->m_fBlood <= 0)
                        {
                            CCLOG("Killed one missile!!!!!!!!!!!!!!!!!!");
                            m_enemyMissileArray->removeObject(missile);
                            missile->removeFromParentAndCleanup(true);
                            missile = NULL;
                        }
                    }
                }
                
            }
        }
    }
    
}

void PlaneManager::updatePlayerBlood()
{
    //238 * 10
    if (m_playerPlane->m_fBlood <= 0 ) {
        m_playerPlane->m_fBlood = 0;
    }
    
    m_spPlayerBlood->removeFromParentAndCleanup(true);
    CCRect rc = CCRectMake(0, 0, 238 * m_playerPlane->m_fBlood / BLOOD_PLAYER, 5);
    m_spPlayerBlood = CCSprite::create(BLOOD_RED_PLAYER, rc);
    
    if (m_spPlayerBlood) {
        //m_spPlayerBlood->setOpacity(100);
        m_spPlayerBlood->setAnchorPoint(ccp(0,0.5));
        m_spPlayerBlood->setPosition(ccp(getWinSize().width / 2 + 140, getWinSize().height - 20));
        this->addChild(m_spPlayerBlood, MIN_ZORDER);
    }
    
    if (m_playerPlane->m_fBlood <= BLOOD_PLAYER / 3) {
        this->schedule(schedule_selector(PlaneManager::helpCallback), m_playerPlane->m_fBlood * 1.0f / BLOOD_PLAYER);
    }
    else
    {
        this->unschedule(schedule_selector(PlaneManager::helpCallback));
        m_spPlayerBlood->setVisible(true);
    }
    
}

void PlaneManager::helpCallback(float t)
{
    m_spPlayerBlood->setVisible(!m_spPlayerBlood->isVisible());
}

void PlaneManager::changePlayerBloodTip(float value)
{
    char szValue[128] = {0};
    value < 0 ? sprintf(szValue, "%d", (int)value) : sprintf(szValue, "+%d", (int)value);
    CCLabelTTF *labelTip = CCLabelTTF::create(szValue, "", 20.0f);
    labelTip->setPosition(getPlayerPlanePosition());
    this->addChild(labelTip);
    //CCScaleBy *scaleby = CCScaleBy::create(0.2f, 3.0f);
    CCFadeOut *fadeout = CCFadeOut::create(1.0f);
    
    // callback
    CCCallFuncN* callback = CCCallFuncN::create(this, callfuncN_selector(PlaneManager::removeTipCallback));
    labelTip->runAction(CCSequence::create(fadeout,callback,NULL));
}

void PlaneManager::removeTipCallback(CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
}