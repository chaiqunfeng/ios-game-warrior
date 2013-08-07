//
//  PlaneManager.h
//  Warrior
//
//  Created by Varek Chai on 5/27/13.
//
//

#ifndef __Warrior__PlaneManager__
#define __Warrior__PlaneManager__

#include <iostream>
#include "BasicLayer.h"
#include "PlayerPlaneLayer.h"
#include "EnemyPlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

class PlaneManager:public BasicLayer
{
public:
    PlaneManager();
    ~PlaneManager();
    
    //static  PlaneManager* sharedPlaneManager();
    virtual bool init();
    CREATE_FUNC(PlaneManager);
    
    CCPoint getPlayerPlanePosition();
    void removeEnemy(CCNode* enemy);
    void removeEnemyBullet(CCNode* enemyBullet);
    void removeMedicine(CCNode* medicine);
    void addMissile(CCPoint po, E_PlaneType pt);
    void setPlayerTouchEnabled(bool t);
    
private:
    
    void startGame();
    
    void addEnemy1Plane(float t);
    void addEnemy2Plane(float t);
    void performAddBossPlane(float t);
    void addMedicine(float t);
    void gameOver();
    
    void hitCheck(float t);
    void updatePlayerBlood();
    void helpCallback(float t);
    
    void changePlayerBloodTip(float value);
    void removeTipCallback(CCNode *pSender);
    
    CCArray *m_enemyArray;
    CCArray *m_enemyBulletArray;
    CCArray *m_enemyMissileArray;
    CCArray *m_medicineArray;
    
    PlayerPlaneLayer *m_playerPlane;
    BulletLayer *m_playerBullet;
    CCSprite* m_spPlayerBlood;
};

#endif /* defined(__Warrior__PlaneManager__) */
