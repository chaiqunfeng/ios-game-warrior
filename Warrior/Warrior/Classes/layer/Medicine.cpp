//
//  Medicine.cpp
//  Warrior
//
//  Created by Varek Chai on 6/17/13.
//
//

#include "Medicine.h"
#include "PlaneManager.h"

#define MEDECINE_IMG_SMALL      "medicine20_20.png"
#define MEDECINE_IMG_BIG        "medicine32_23.png"

Medicine::Medicine()
{
}

Medicine::~Medicine()
{
}

Medicine *Medicine::create(bool small)
{
    Medicine *pRet = new Medicine();
    if (pRet && pRet->init(small))
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

bool Medicine::init(bool small)
{
    if (CCSprite::init())
    {
        m_bReceived = false;
        
        initWithFile(small? MEDECINE_IMG_SMALL: MEDECINE_IMG_BIG);
        m_fBloodCapacity = small? MEDICINE_BLOOD_CAPACITY_SMALL: MEDICINE_BLOOD_CAPACITY_BIG;
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        float randomX = CCRANDOM_0_1() * size.width;
        float randomY = CCRANDOM_0_1() * size.height;
        setPosition(ccp(randomX, randomY));
                
        CCRotateBy *rotate = CCRotateBy::create(1, 10);
        CCRepeatForever *repeatRotate = CCRepeatForever::create(rotate);
        
        CCFadeIn *fadein = CCFadeIn::create(3);
        runAction(fadein);
        runAction(repeatRotate);
        
        this->schedule(schedule_selector(Medicine::blinkCallback), 0.3f, kCCRepeatForever, 10);
        this->scheduleOnce(schedule_selector(Medicine::removeCallback), 15);
        return true;
    }
    return false;
}

float Medicine::bloodCapacity()
{
    return m_fBloodCapacity;
}

void Medicine::setReceived()
{
    m_bReceived = true;
    
    this->unschedule(schedule_selector(Medicine::blinkCallback));
    
    stopAllActions();
    CCScaleBy *scaleby = CCScaleBy::create(0.2f, 3.0f);
    CCFadeOut *fadeout = CCFadeOut::create(0.2);
    runAction(scaleby);
    runAction(fadeout);
}

bool Medicine::isReceived()
{
    return m_bReceived;
}

void Medicine::blinkCallback(float t)
{
    if (getOpacity() == 255) {
        setOpacity(25);
    }
    else {
        setOpacity(255);
    }
}

void Medicine::removeCallback(float t)
{
    PlaneManager *parent = (PlaneManager *)getParent();
    parent->removeMedicine(this);
}
